# Use Ubuntu as base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install essential development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    gcc \
    make \
    cmake \
    gdb \
    valgrind \
    doxygen \
    graphviz \
    git \
    wget \
    pkg-config \
    libasan6 \
    llvm \
    coreutils \
    && rm -rf /var/lib/apt/lists/*

# Install Google Test from source (for better compatibility)
RUN cd /tmp && \
    git clone https://github.com/google/googletest.git && \
    cd googletest && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd / && \
    rm -rf /tmp/googletest

# Set up working directory
WORKDIR /workspace

# FIX: Configure AddressSanitizer to not buffer output
# These options ensure output is displayed immediately
ENV ASAN_OPTIONS=halt_on_error=0:print_stats=0:verbosity=0:log_path=stderr:print_module_map=0:print_legend=0

# Create an empty suppressions file to avoid warnings
RUN touch /tmp/lsan_suppressions.txt
ENV LSAN_OPTIONS=suppressions=/tmp/lsan_suppressions.txt

# Default command
CMD ["/bin/bash"]
