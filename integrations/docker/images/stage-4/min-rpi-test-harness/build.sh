#!/bin/bash
#
# Raspberry Pi Image Builder
# Creates customized Ubuntu 24.04 Raspberry Pi images with cloud-init configuration
#
set -euo pipefail

# =============================================================================
# Configuration
# =============================================================================

# Configuration
UBUNTU_VERSION="24.04.3"
ARCH="arm64"
TARGET="raspi"
IMAGE_NAME="ubuntu-${UBUNTU_VERSION}-preinstalled-server-${ARCH}+${TARGET}.img"
IMAGE_XZ="${IMAGE_NAME}.xz"

BASE_IMAGE_URL="https://cdimage.ubuntu.com/releases/24.04/release/${IMAGE_XZ}"
BASE_IMAGE_NAME=$IMAGE_XZ
BASE_IMAGE_UNCOMPRESSED=$IMAGE_NAME

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CACHE_DIR="/build/cache"
WORK_DIR="/build/work"
OUTPUT_DIR="/build/output"
CONFIG_DIR="${SCRIPT_DIR}/config"

# Matter binary extraction configuration
DOCKER_IMAGE="${DOCKER_IMAGE:-connectedhomeip/chip-cert-bins}"
DOCKER_TAG="${DOCKER_TAG:-bab3aa0773551c0661e17b34b0e97b4e5813b45e}"
MATTER_BINARIES_DIR="${WORK_DIR}/matter-binaries"
MATTER_TARGET_DIR="/opt/matter-bins"

# Runtime state
LOOP_DEV=""
BOOT_PART=""
ROOT_PART=""
BOOT_MOUNTED=false
ROOT_MOUNTED=false
USE_KPARTX=false
CONTAINER_ID=""
MATTER_BINARY_COUNT=0
COMPRESSED_IMAGE=""

# =============================================================================
# Utility Functions
# =============================================================================

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*"
}

error() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] ERROR: $*" >&2
}

# =============================================================================
# Dependency and Permission Checks
# =============================================================================

check_root() {
    if [[ $EUID -ne 0 ]]; then
        error "This script must be run as root (use sudo)"
        exit 2
    fi
}

check_dependencies() {
    local missing=()
    local deps=(wget xz losetup mount umount kpartx)

    for cmd in "${deps[@]}"; do
        if ! command -v "$cmd" &>/dev/null; then
            missing+=("$cmd")
        fi
    done

    if [[ ${#missing[@]} -gt 0 ]]; then
        error "Missing required tools: ${missing[*]}"
        exit 1
    fi

    log "All dependencies satisfied"
}


# =============================================================================
# Cleanup (trap handler)
# =============================================================================

cleanup() {
    log "Cleaning up..."
    set +e  # Don't exit on cleanup errors

    # Unmount root partition if mounted
    if [[ "$ROOT_MOUNTED" == true ]]; then
        if mountpoint -q "${WORK_DIR}/mnt/root" 2>/dev/null; then
            sync
            umount "${WORK_DIR}/mnt/root" 2>/dev/null || umount -l "${WORK_DIR}/mnt/root" 2>/dev/null || true
            log "Unmounted root partition"
        fi
        ROOT_MOUNTED=false
    fi

    # Unmount boot partition if mounted
    if [[ "$BOOT_MOUNTED" == true ]]; then
        if mountpoint -q "${WORK_DIR}/mnt/boot" 2>/dev/null; then
            sync
            umount "${WORK_DIR}/mnt/boot" 2>/dev/null || umount -l "${WORK_DIR}/mnt/boot" 2>/dev/null || true
            log "Unmounted boot partition"
        fi
        BOOT_MOUNTED=false
    fi

    # Remove kpartx mappings if used
    if [[ "$USE_KPARTX" == true ]] && [[ -n "${LOOP_DEV}" ]]; then
        kpartx -d "${LOOP_DEV}" 2>/dev/null || true
        log "Removed kpartx mappings"
    fi

    # Detach loopback device if attached
    if [[ -n "${LOOP_DEV}" ]]; then
        losetup -d "${LOOP_DEV}" 2>/dev/null || true
        log "Detached loopback device ${LOOP_DEV}"
        LOOP_DEV=""
    fi

    # Docker container cleanup
    cleanup_docker
    
    set -e
}

# Set trap to ensure cleanup runs on exit
trap cleanup EXIT


# =============================================================================
# Docker and Matter Binary Extraction
# =============================================================================

check_docker() {
    if ! command -v docker &>/dev/null; then
        log "WARNING: Docker not available, skipping Matter binary extraction"
        return 1
    fi
    if ! docker info &>/dev/null; then
        log "WARNING: Docker daemon not running, skipping Matter binary extraction"
        return 1
    fi
    return 0
}

cleanup_docker() {
    if [[ -n "${CONTAINER_ID}" ]]; then
        docker rm "${CONTAINER_ID}" >/dev/null 2>&1 || true
        log "Removed temporary container"
        CONTAINER_ID=""
    fi
}

extract_matter_binaries() {
    log "Extracting Matter binaries from Docker image..."

    # Create binaries directory
    mkdir -p "${MATTER_BINARIES_DIR}"

    # Pull Docker image with ARM64 platform
    log "Pulling Docker image ${DOCKER_IMAGE}:${DOCKER_TAG}..."
    if ! docker pull --platform linux/arm64 "${DOCKER_IMAGE}:${DOCKER_TAG}"; then
        error "Failed to pull Docker image"
        exit 9
    fi

    # Create temporary container without starting it
    log "Creating temporary container..."
    CONTAINER_ID=$(docker create --platform linux/arm64 "${DOCKER_IMAGE}:${DOCKER_TAG}")
    if [[ -z "${CONTAINER_ID}" ]]; then
        error "Failed to create temporary container"
        exit 10
    fi
    log "Created container: ${CONTAINER_ID}"

    # Try to copy /root/apps directory first
    log "Attempting to copy /root/apps directory..."
    if docker cp "${CONTAINER_ID}:/root/apps" "${MATTER_BINARIES_DIR}/" 2>/dev/null; then
        log "Successfully copied /root/apps directory"
    else
        # Fallback: try to copy individual known binaries from /root/
        log "Directory /root/apps not found, attempting to copy individual binaries..."
        local binaries_found=false
        local known_binaries=(
            "chip-tool"
            "chip-cert"
            "chip-all-clusters-app"
            "chip-lighting-app"
            "chip-lock-app"
            "chip-ota-provider-app"
            "chip-ota-requestor-app"
        )

        for binary in "${known_binaries[@]}"; do
            if docker cp "${CONTAINER_ID}:/root/${binary}" "${MATTER_BINARIES_DIR}/" 2>/dev/null; then
                log "Copied ${binary}"
                binaries_found=true
            fi
        done

        if [[ "${binaries_found}" == false ]]; then
            error "Failed to extract any Matter binaries from container"
            cleanup_docker
            exit 11
        fi
    fi

    # Remove temporary container
    cleanup_docker
    log "Matter binary extraction complete"
}

prepare_matter_binaries() {
    log "Preparing Matter binaries..."

    # Move binaries from apps/ subdirectory to root level if needed
    if [[ -d "${MATTER_BINARIES_DIR}/apps" ]]; then
        log "Moving binaries from apps/ subdirectory to root level..."
        # Move all files from apps/ to the binaries directory
        find "${MATTER_BINARIES_DIR}/apps" -type f -exec mv {} "${MATTER_BINARIES_DIR}/" \;
        # Remove the now-empty apps directory
        rm -rf "${MATTER_BINARIES_DIR}/apps"
        log "Binaries moved to root level"
    fi

    # Set executable permissions on all binary files
    log "Setting executable permissions on binaries..."
    find "${MATTER_BINARIES_DIR}" -type f ! -name "*.txt" -exec chmod +x {} \;

    # Count binaries for reporting
    MATTER_BINARY_COUNT=$(find "${MATTER_BINARIES_DIR}" -type f ! -name "*.txt" | wc -l)
    log "Found ${MATTER_BINARY_COUNT} binary files"

    # Get Docker image ID for manifest
    local docker_image_id
    docker_image_id=$(docker inspect --format='{{.Id}}' "${DOCKER_IMAGE}:${DOCKER_TAG}" 2>/dev/null || echo "unknown")

    # Create extraction manifest
    local manifest_file="${MATTER_BINARIES_DIR}/EXTRACTION_INFO.txt"
    log "Creating extraction manifest..."
    
    cat > "${manifest_file}" <<EOF
Matter Binaries Extracted From: ${DOCKER_IMAGE}:${DOCKER_TAG}
Extraction Date: $(date -u +%Y-%m-%dT%H:%M:%SZ)
Docker Image ID: ${docker_image_id}
Total Binaries: ${MATTER_BINARY_COUNT}

Binaries:
EOF

    # List all binaries in the manifest
    find "${MATTER_BINARIES_DIR}" -type f ! -name "*.txt" -printf "- %f\n" >> "${manifest_file}"

    # Ensure manifest does NOT have executable permissions
    chmod 644 "${manifest_file}"

    log "Matter binaries prepared successfully"
}

# =============================================================================
# Image Download
# =============================================================================

download_image() {
    mkdir -p "${CACHE_DIR}"

    # Download base image if not cached
    if [[ -f "${CACHE_DIR}/${BASE_IMAGE_NAME}" ]]; then
        # Verify file is not empty
        if [[ -s "${CACHE_DIR}/${BASE_IMAGE_NAME}" ]]; then
            log "Base image already cached, skipping download"
            return 0
        else
            log "Cached image is empty, re-downloading..."
            rm -f "${CACHE_DIR}/${BASE_IMAGE_NAME}"
        fi
    fi

    log "Downloading base image from ${BASE_IMAGE_URL}..."
    wget --progress=bar:force -O "${CACHE_DIR}/${BASE_IMAGE_NAME}" "${BASE_IMAGE_URL}"

    if [[ $? -ne 0 ]] || [[ ! -s "${CACHE_DIR}/${BASE_IMAGE_NAME}" ]]; then
        error "Failed to download base image"
        rm -f "${CACHE_DIR}/${BASE_IMAGE_NAME}"
        exit 3
    fi

    log "Download complete"
}


# =============================================================================
# Image Preparation
# =============================================================================

decompress_image() {
    log "Decompressing image..."

    mkdir -p "${WORK_DIR}"

    # Remove any existing working image
    rm -f "${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}"

    # Decompress using xz (keep original)
    xz -dk "${CACHE_DIR}/${BASE_IMAGE_NAME}" -c > "${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}"

    if [[ $? -ne 0 ]]; then
        error "Failed to decompress image"
        exit 5
    fi

    log "Image decompressed to ${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}"
}

expand_image() {
    local expand_size="${1:-4G}"
    log "Expanding image by ${expand_size} for Matter binaries..."

    local image_file="${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}"

    # Expand the image file
    truncate -s "+${expand_size}" "${image_file}"

    if [[ $? -ne 0 ]]; then
        error "Failed to expand image file"
        exit 14
    fi

    log "Image file expanded by ${expand_size}"

    # Attach to loopback to resize partition
    local temp_loop
    temp_loop=$(losetup -f --show "${image_file}")

    # Use parted to resize partition 2 (root) to use all available space
    log "Resizing root partition to use expanded space..."
    parted -s "${temp_loop}" resizepart 2 100%

    if [[ $? -ne 0 ]]; then
        losetup -d "${temp_loop}"
        error "Failed to resize partition"
        exit 14
    fi

    # Create partition mappings to resize filesystem
    kpartx -av "${temp_loop}"
    local loop_name
    loop_name=$(basename "${temp_loop}")
    local root_part="/dev/mapper/${loop_name}p2"

    # Wait for partition device
    local retries=10
    while [[ $retries -gt 0 ]]; do
        if [[ -b "${root_part}" ]]; then
            break
        fi
        sleep 1
        retries=$((retries - 1))
    done

    # Check and resize the ext4 filesystem
    log "Checking filesystem before resize..."
    e2fsck -f -y "${root_part}" || true

    log "Resizing ext4 filesystem..."
    resize2fs "${root_part}"

    if [[ $? -ne 0 ]]; then
        kpartx -d "${temp_loop}"
        losetup -d "${temp_loop}"
        error "Failed to resize filesystem"
        exit 14
    fi

    # Cleanup temporary loopback
    kpartx -d "${temp_loop}"
    losetup -d "${temp_loop}"

    log "Image expansion complete"
}


setup_loopback() {
    log "Setting up loopback device..."

    # Attach image to loopback device
    LOOP_DEV=$(losetup -f --show "${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}")

    if [[ -z "$LOOP_DEV" ]]; then
        error "Failed to setup loopback device"
        exit 6
    fi

    log "Attached image to ${LOOP_DEV}"

    # Use kpartx to create partition mappings
    log "Creating partition mappings with kpartx..."
    kpartx -av "${LOOP_DEV}"
    USE_KPARTX=true
    
    # kpartx creates /dev/mapper/loopXp1, /dev/mapper/loopXp2, etc.
    # Extract loop number from device name
    local loop_name
    loop_name=$(basename "${LOOP_DEV}")
    BOOT_PART="/dev/mapper/${loop_name}p1"
    
    # Wait for partition device to appear
    local retries=10
    while [[ $retries -gt 0 ]]; do
        if [[ -b "${BOOT_PART}" ]]; then
            break
        fi
        log "Waiting for partition device ${BOOT_PART}..."
        sleep 1
        retries=$((retries - 1))
    done

    # Verify boot partition exists
    if [[ ! -b "${BOOT_PART}" ]]; then
        log "Available devices in /dev/mapper:"
        ls -la /dev/mapper/ 2>/dev/null || true
        error "Boot partition not found at ${BOOT_PART}"
        exit 6
    fi

    log "Loopback device ready with partitions (boot: ${BOOT_PART})"
}

mount_boot() {
    log "Mounting boot partition..."

    mkdir -p "${WORK_DIR}/mnt/boot"

    mount "${BOOT_PART}" "${WORK_DIR}/mnt/boot"

    if [[ $? -ne 0 ]]; then
        error "Failed to mount boot partition"
        exit 7
    fi

    BOOT_MOUNTED=true
    log "Boot partition mounted at ${WORK_DIR}/mnt/boot"
}

mount_root() {
    log "Mounting root partition..."

    # Extract loop number from device name to construct root partition path
    local loop_name
    loop_name=$(basename "${LOOP_DEV}")
    ROOT_PART="/dev/mapper/${loop_name}p2"

    # Wait for partition device to appear
    local retries=10
    while [[ $retries -gt 0 ]]; do
        if [[ -b "${ROOT_PART}" ]]; then
            break
        fi
        log "Waiting for partition device ${ROOT_PART}..."
        sleep 1
        retries=$((retries - 1))
    done

    # Verify root partition exists
    if [[ ! -b "${ROOT_PART}" ]]; then
        log "Available devices in /dev/mapper:"
        ls -la /dev/mapper/ 2>/dev/null || true
        error "Root partition not found at ${ROOT_PART}"
        exit 12
    fi

    mkdir -p "${WORK_DIR}/mnt/root"

    mount "${ROOT_PART}" "${WORK_DIR}/mnt/root"

    if [[ $? -ne 0 ]]; then
        error "Failed to mount root partition"
        exit 12
    fi

    ROOT_MOUNTED=true
    log "Root partition mounted at ${WORK_DIR}/mnt/root"
}


# =============================================================================
# Matter Binary Injection
# =============================================================================

inject_matter_binaries() {
    log "Injecting Matter binaries into root filesystem..."

    # Check if we have binaries to inject
    if [[ ! -d "${MATTER_BINARIES_DIR}" ]] || [[ -z "$(ls -A "${MATTER_BINARIES_DIR}" 2>/dev/null)" ]]; then
        log "No Matter binaries to inject, skipping"
        return 0
    fi

    # Verify root partition is mounted
    if [[ "$ROOT_MOUNTED" != true ]]; then
        error "Root partition not mounted, cannot inject Matter binaries"
        exit 13
    fi

    local root_mount="${WORK_DIR}/mnt/root"
    local target_dir="${root_mount}${MATTER_TARGET_DIR}"

    # Create target directory /opt/matter-bins/ in root filesystem
    log "Creating target directory ${MATTER_TARGET_DIR}..."
    mkdir -p "${target_dir}"

    if [[ $? -ne 0 ]]; then
        error "Failed to create target directory ${target_dir}"
        exit 13
    fi

    # Copy all binaries preserving permissions
    log "Copying Matter binaries to ${MATTER_TARGET_DIR}..."
    cp -a "${MATTER_BINARIES_DIR}/"* "${target_dir}/"

    if [[ $? -ne 0 ]]; then
        error "Failed to copy Matter binaries to root filesystem"
        exit 13
    fi

    # Count injected binaries for reporting
    local injected_count
    injected_count=$(find "${target_dir}" -type f ! -name "*.txt" | wc -l)

    log "Successfully injected ${injected_count} Matter binaries to ${MATTER_TARGET_DIR}"
}

# =============================================================================
# Cloud-init Injection
# =============================================================================

inject_cloudinit() {
    log "Injecting cloud-init configuration..."

    local boot_mount="${WORK_DIR}/mnt/boot"
    local timestamp
    timestamp=$(date +%Y%m%d%H%M%S)

    # Copy user-data
    if [[ -f "${CONFIG_DIR}/user-data" ]]; then
        cp "${CONFIG_DIR}/user-data" "${boot_mount}/user-data"
        log "Copied user-data"
    else
        error "user-data file not found in ${CONFIG_DIR}"
        exit 8
    fi

    # Copy network-config
    if [[ -f "${CONFIG_DIR}/network-config" ]]; then
        cp "${CONFIG_DIR}/network-config" "${boot_mount}/network-config"
        log "Copied network-config"
    else
        error "network-config file not found in ${CONFIG_DIR}"
        exit 8
    fi

    # Generate meta-data with unique instance-id
    if [[ -f "${CONFIG_DIR}/meta-data" ]]; then
        sed "s/TIMESTAMP/${timestamp}/g" "${CONFIG_DIR}/meta-data" > "${boot_mount}/meta-data"
        log "Generated meta-data with instance-id: iid-rpi-${timestamp}"
    else
        # Create minimal meta-data if template doesn't exist
        cat > "${boot_mount}/meta-data" <<EOF
instance-id: iid-rpi-${timestamp}
local-hostname: ubuntu
EOF
        log "Created meta-data with instance-id: iid-rpi-${timestamp}"
    fi

    # Copy boot configuration files
    if [[ -f "${CONFIG_DIR}/config.txt" ]]; then
        cp "${CONFIG_DIR}/config.txt" "${boot_mount}/config.txt"
        log "Copied config.txt"
    fi

    if [[ -f "${CONFIG_DIR}/cmdline.txt" ]]; then
        cp "${CONFIG_DIR}/cmdline.txt" "${boot_mount}/cmdline.txt"
        log "Copied cmdline.txt"
    fi

    if [[ -f "${CONFIG_DIR}/boot.scr" ]]; then
        cp "${CONFIG_DIR}/boot.scr" "${boot_mount}/boot.scr"
        log "Copied boot.scr"
    fi

    log "Cloud-init configuration injected successfully"
}


# =============================================================================
# Output Generation
# =============================================================================

finalize_image() {
    log "Finalizing image..."

    # Sync filesystem
    sync

    # Unmount root partition before copying
    if [[ "$ROOT_MOUNTED" == true ]]; then
        umount "${WORK_DIR}/mnt/root"
        ROOT_MOUNTED=false
        log "Unmounted root partition"
    fi

    # Unmount boot partition before copying
    if [[ "$BOOT_MOUNTED" == true ]]; then
        umount "${WORK_DIR}/mnt/boot"
        BOOT_MOUNTED=false
        log "Unmounted boot partition"
    fi

    # Remove kpartx mappings
    if [[ "$USE_KPARTX" == true ]] && [[ -n "${LOOP_DEV}" ]]; then
        kpartx -d "${LOOP_DEV}"
        USE_KPARTX=false
        log "Removed kpartx mappings"
    fi

    # Detach loopback
    if [[ -n "${LOOP_DEV}" ]]; then
        losetup -d "${LOOP_DEV}"
        log "Detached loopback device"
        LOOP_DEV=""
    fi

    # Create output directory
    mkdir -p "${OUTPUT_DIR}"

    # Generate timestamped output filename
    local timestamp
    timestamp=$(date +%Y%m%d-%H%M%S)
    OUTPUT_IMAGE="${OUTPUT_DIR}/rpi-ubuntu-24.04-${timestamp}.img"

    # Copy working image to output
    cp "${WORK_DIR}/${BASE_IMAGE_UNCOMPRESSED}" "${OUTPUT_IMAGE}"

    log "Image finalized: ${OUTPUT_IMAGE}"
}


compress_image() {
    log "Compressing image with gzip..."

    local compressed_image="${OUTPUT_IMAGE}.gz"

    # Compress with gzip (level 6, no original filename/timestamp for reproducibility)
    gzip -6 -n -c "${OUTPUT_IMAGE}" > "${compressed_image}"

    if [[ $? -ne 0 ]]; then
        error "Failed to compress image"
        exit 15
    fi

    local compressed_size
    compressed_size=$(du -h "${compressed_image}" | awk '{print $1}')
    log "Compressed image: ${compressed_image} (${compressed_size})"

    COMPRESSED_IMAGE="${compressed_image}"
}

generate_checksum() {
    log "Generating checksums..."

    local checksum_file="${OUTPUT_IMAGE}.sha256"
    local compressed_checksum_file="${COMPRESSED_IMAGE}.sha256"

    # Generate SHA256 checksum for uncompressed image
    sha256sum "${OUTPUT_IMAGE}" | awk '{print $1}' > "${checksum_file}"
    log "Checksum saved to ${checksum_file}"

    # Generate SHA256 checksum for compressed image
    sha256sum "${COMPRESSED_IMAGE}" | awk '{print $1}' > "${compressed_checksum_file}"
    log "Checksum saved to ${compressed_checksum_file}"

    # Report final output
    local size
    local compressed_size
    size=$(du -h "${OUTPUT_IMAGE}" | awk '{print $1}')
    compressed_size=$(du -h "${COMPRESSED_IMAGE}" | awk '{print $1}')

    echo ""
    echo "=========================================="
    echo "BUILD COMPLETE"
    echo "=========================================="
    echo "Output image:      ${OUTPUT_IMAGE}"
    echo "Image size:        ${size}"
    echo "Checksum:          $(cat "${checksum_file}")"
    echo ""
    echo "Compressed image:  ${COMPRESSED_IMAGE}"
    echo "Compressed size:   ${compressed_size}"
    echo "Checksum:          $(cat "${compressed_checksum_file}")"
    if [[ ${MATTER_BINARY_COUNT} -gt 0 ]]; then
        echo ""
        echo "Matter bins:       ${MATTER_BINARY_COUNT} binaries included"
    else
        echo ""
        echo "Matter bins:       None (Docker not available or extraction skipped)"
    fi
    echo "=========================================="
}


# =============================================================================
# Main Execution
# =============================================================================

main() {
    echo ""
    echo "=========================================="
    echo "Raspberry Pi Image Builder"
    echo "=========================================="
    echo ""

    # Pre-flight checks
    check_root
    check_dependencies

    # Extract Matter binaries from Docker (before image download)
    if check_docker; then
        extract_matter_binaries
        prepare_matter_binaries
    fi

    # Download base image
    download_image

    # Prepare working image
    decompress_image
    expand_image "4G"  # Expand root partition by 4GB for Matter binaries
    setup_loopback
    mount_boot
    mount_root

    # Inject cloud-init configuration
    inject_cloudinit

    # Inject Matter binaries into root filesystem
    inject_matter_binaries

    # Generate output
    finalize_image
    compress_image
    generate_checksum

    log "Build completed successfully"
}

# Run main function
main "$@"
