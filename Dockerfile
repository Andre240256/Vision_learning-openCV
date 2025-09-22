# Use Ubuntu 22.04 as base image
FROM ubuntu:22.04

# Set environment variables to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libopencv-dev \
    libopencv-contrib-dev \
    libgtk-3-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    gfortran \
    libatlas-base-dev \
    libtbb2 \
    libtbb-dev \
    libopenexr-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer1.0-dev \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy the entire project
COPY . .

# Create build directory
RUN mkdir -p build

# Build the project
WORKDIR /app/build
RUN cmake .. && make

# Set the executable permissions
RUN chmod +x src/virtualPaint

# Switch back to app directory
WORKDIR /app

# Create a script to run the application
RUN echo '#!/bin/bash\ncd /app/build && ./src/virtualPaint' > /app/run_virtualpaint.sh && \
    chmod +x /app/run_virtualpaint.sh

# Expose display for GUI applications
ENV DISPLAY=:0
ENV QT_X11_NO_MITSHM=1
ENV QT_SCALE_FACTOR=1
ENV GDK_SCALE=1
ENV GDK_DPI_SCALE=1

# Default command
CMD ["/app/run_virtualpaint.sh"]