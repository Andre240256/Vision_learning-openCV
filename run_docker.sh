#!/bin/bash

# Docker run script for virtualPaint

echo "Running virtualPaint in Docker..."

# Check if Docker is running
if ! docker info >/dev/null 2>&1; then
    echo "Error: Docker is not running. Please start Docker and try again."
    exit 1
fi

# Check if the image exists
if ! docker image inspect virtualpaint:latest >/dev/null 2>&1; then
    echo "Error: virtualPaint Docker image not found. Please build it first:"
    echo "  ./build_docker.sh"
    exit 1
fi

# Allow X11 forwarding for GUI applications
xhost +local:docker

echo "Starting virtualPaint application..."
echo "Make sure your camera is connected and accessible at /dev/video0"
echo "Press Ctrl+C to stop the application"

# Run the container with camera and display access
docker run -it --rm \
    --privileged \
    --device=/dev/video0:/dev/video0 \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    --name virtualpaint-container \
    virtualpaint:latest

# Restore X11 security
xhost -local:docker

echo "virtualPaint application stopped."