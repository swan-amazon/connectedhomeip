#!/bin/bash
#
# Run the Raspberry Pi image builder in a Docker container
# This allows building on macOS where losetup is not available
#
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_NAME="rpi-image-builder"

# Create mount
mkdir -p ${SCRIPT_DIR}/build/{cache,output,work}

echo "Building Docker image..."
docker build -t "${IMAGE_NAME}" "${SCRIPT_DIR}"

echo "Running build in container..."
# --privileged is required for losetup to work inside the container
# Mount directories for caching and output persistence
# Mount Docker socket to allow Matter binary extraction from Docker images
docker run --rm \
    --privileged \
    -v /var/run/docker.sock:/var/run/docker.sock \
    --mount "type=bind,source=${SCRIPT_DIR}/build,target=/build" \
    --workdir "/host" \
    "${IMAGE_NAME}"

echo ""
echo "Build complete. Output is in: ${SCRIPT_DIR}/build/output/"
