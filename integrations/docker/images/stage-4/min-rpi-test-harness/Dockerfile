FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    wget \
    xz-utils \
    mount \
    util-linux \
    coreutils \
    fdisk \
    parted \
    kpartx \
    e2fsprogs \
    ca-certificates \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install Docker CLI (not daemon - we'll use host's Docker via socket)
RUN curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc \
    && chmod a+r /etc/apt/keyrings/docker.asc \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu $(. /etc/os-release && echo "$VERSION_CODENAME") stable" > /etc/apt/sources.list.d/docker.list \
    && apt-get update \
    && apt-get install -y docker-ce-cli \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /host

COPY build.sh /host/
COPY config/ /host/config/

RUN chmod +x /host/build.sh

CMD ["/host/build.sh"]
