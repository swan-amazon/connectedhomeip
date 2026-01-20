# Raspberry Pi Matter Test Image Builder

A tool for creating customized Ubuntu 24.04 Raspberry Pi images pre-loaded with Matter (Connected Home over IP) certification binaries for smart home device testing.

## Overview

This tool:
1. Downloads the official Ubuntu 24.04 LTS Raspberry Pi image
2. Extracts Matter certification binaries from a configurable Docker image
3. Expands the root partition to accommodate the binaries
4. Injects cloud-init configuration and Matter binaries
5. Produces a ready-to-flash .img file

The resulting image boots with all Matter tools available at `/opt/matter-bins/`, ready for testing of Matter-compatible devices.

## Prerequisites

- macOS or Linux with Docker installed
- ~10GB free disk space (for image building and Matter binaries)

## Quick Start

```bash
./docker-build.sh
```

The build runs inside a Docker container, so no additional dependencies are needed on your host system.

## Output

After a successful build:
```
build/output/
├── rpi-ubuntu-24.04-YYYYMMDD-HHMMSS.img      # ~6GB image file
└── rpi-ubuntu-24.04-YYYYMMDD-HHMMSS.img.sha256
```

Build completion shows:
```
==========================================
BUILD COMPLETE
==========================================
Output image: /build/output/rpi-ubuntu-24.04-20241229-213524.img
Image size:   5.8G
Checksum:     abc123...
Matter bins:  42 binaries included
==========================================
```

## Flashing the Image

Using `dd` (Linux/macOS):
```bash
sudo dd if=build/output/rpi-ubuntu-24.04-*.img of=/dev/sdX bs=4M status=progress
sync
```

Or use [Raspberry Pi Imager](https://www.raspberrypi.com/software/) → "Use custom" → select the .img file.

## Matter Binaries

The image includes all certification binaries from the Connected Home IP project:

| Binary | Purpose |
|--------|---------|
| `chip-tool` | Matter controller/commissioner CLI |
| `chip-cert` | Certificate generation and management |
| `chip-all-clusters-app` | Test app with all cluster implementations |
| `chip-lighting-app` | Lighting device test application |
| `chip-lock-app` | Door lock test application |
| `chip-ota-provider-app` | OTA update provider |
| ... | And 30+ more certification apps |

After boot, binaries are available at `/opt/matter-bins/`:
```bash
/opt/matter-bins/chip-tool pairing onnetwork 1 20202021
```

## Configuration

### Cloud-init Files

Configuration files in `config/`:

| File | Purpose |
|------|---------|
| `user-data` | Users, packages, hostname, SSH settings |
| `network-config` | Network configuration (DHCP, WiFi) |
| `meta-data` | Instance metadata |

### Default Settings

- Hostname: `matter-test`
- User: `ubuntu` / Password: `ubuntu`
- SSH password auth: enabled
- Packages: avahi/mDNS, development libraries, Python 3

### Customizing the Docker Tag

To use a different version of Matter binaries:
```bash
DOCKER_TAG=latest ./docker-build.sh
```

Or edit `DOCKER_TAG` in `build.sh`.

## Directory Structure

```
rpi-image-builder/
├── build.sh           # Main build script
├── docker-build.sh    # Docker wrapper for macOS/cross-platform builds
├── Dockerfile         # Build container definition
├── config/            # Cloud-init configuration
│   ├── user-data
│   ├── network-config
│   └── meta-data
└── build/             # Build artifacts (gitignored)
    ├── cache/         # Downloaded base images
    ├── work/          # Working directory
    └── output/        # Final images
```

## Post-Boot Verification

After flashing and booting the Pi:

```bash
# SSH into the Pi
ssh ubuntu@matter-test.local

# Verify Matter binaries
ls /opt/matter-bins/

# Check extraction manifest
cat /opt/matter-bins/EXTRACTION_INFO.txt

# Test chip-tool
/opt/matter-bins/chip-tool version
```

## Troubleshooting

**Docker not available**: Ensure Docker Desktop is running. The build requires Docker to extract Matter binaries.

**Build fails with "No space left"**: The image expansion may have failed. Check that `e2fsprogs` is installed in the container.

**Matter binaries not found after boot**: Check the build output for "Matter bins: X binaries included". If it shows 0 or "None", Docker wasn't available during the build.

**Network not working**: The default config uses DHCP on ethernet. For WiFi, edit `config/network-config` before building.

## License

MIT
