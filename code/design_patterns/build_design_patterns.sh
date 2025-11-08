#!/bin/bash

# Bash script to build the design patterns project using CMake and Make
set -e
echo "Building design patterns project..."

# Navigate to the project directory
cd "$(dirname "$0")"
# Create build directory if it doesn't exist
mkdir -p build
# Navigate to build directory
cd build
# Run CMake to configure the project
cmake ..
# Build the project using Make
make

echo "Build completed successfully."

