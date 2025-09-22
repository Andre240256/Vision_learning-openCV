#!/bin/bash

# Docker Compose script for virtualPaint

echo "Running virtualPaint with Docker Compose..."

# Check if Docker and docker-compose are available
if ! docker info >/dev/null 2>&1; then
    echo "Error: Docker is not running. Please start Docker and try again."
    exit 1
fi

if ! command -v docker-compose >/dev/null 2>&1; then
    echo "Error: docker-compose is not installed. Please install docker-compose and try again."
    exit 1
fi

# Setup X11 forwarding for GUI applications
echo "Setting up X11 forwarding..."
xhost +local:docker

# Create X11 authorization file if it doesn't exist
if [ ! -f ~/.Xauthority ]; then
    touch ~/.Xauthority
fi

echo "Starting virtualPaint application with Docker Compose..."
echo "Make sure your camera is connected and accessible at /dev/video0"
echo "Press Ctrl+C to stop the application"

# Run with docker-compose
docker-compose up --build

# Restore X11 security
echo "Cleaning up X11 permissions..."
xhost -local:docker

echo "virtualPaint application stopped."