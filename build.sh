#!/bin/bash

# Manual build script for DSA Library
# This script compiles the project without CMake

echo "Building DSA Library..."

CXX=${CXX:-clang++}
CXXFLAGS="-std=c++17 -Wall -Wextra -I./include"

# Create build directory
mkdir -p build

# Compile main executable
echo "Compiling main executable..."
$CXX $CXXFLAGS src/main.cpp -o build/DSA_Library
if [ $? -eq 0 ]; then
    echo "✓ DSA_Library compiled successfully"
else
    echo "✗ Failed to compile DSA_Library"
    exit 1
fi

# Compile examples
echo "Compiling examples..."
$CXX $CXXFLAGS examples/usage_examples.cpp -o build/DSA_Examples
if [ $? -eq 0 ]; then
    echo "✓ DSA_Examples compiled successfully"
else
    echo "✗ Failed to compile DSA_Examples"
    exit 1
fi

# Compile tests
echo "Compiling tests..."
$CXX $CXXFLAGS tests/test_data_structures.cpp -o build/DSA_Tests
if [ $? -eq 0 ]; then
    echo "✓ DSA_Tests compiled successfully"
else
    echo "✗ Failed to compile DSA_Tests"
    exit 1
fi

echo ""
echo "╔═══════════════════════════════════════╗"
echo "║  Build completed successfully!        ║"
echo "║                                       ║"
echo "║  Run the programs:                   ║"
echo "║  ./build/DSA_Library                 ║"
echo "║  ./build/DSA_Examples                ║"
echo "║  ./build/DSA_Tests                   ║"
echo "╚═══════════════════════════════════════╝"
