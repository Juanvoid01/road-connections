#!/bin/bash

# Check if the script is being executed at the same level as CMakeLists.txt
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: This script must be executed in the same directory level as CMakeLists.txt."
    exit 1
fi

# Create and configure the build debug and release directory
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
cd ../..
mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
cd ../..
