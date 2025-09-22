#!/bin/bash

# Docker build script for virtualPaint

echo "Building virtualPaint Docker image..."

# Check if Docker is running
if ! docker info >/dev/null 2>&1; then
    echo "Error: Docker is not running. Please start Docker and try again."
    exit 1
fi

# Build the Docker image
docker build -t virtualpaint:latest .

if [ $? -eq 0 ]; then
    echo "✅ Docker image built successfully!"
    echo "Image name: virtualpaint:latest"
    echo ""
    echo "To run the application, use:"
    echo "  ./run_docker.sh"
    echo "or"
    echo "  docker-compose up"
else
    echo "❌ Failed to build Docker image"
    exit 1
fi