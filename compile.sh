#!/bin/bash
# Automation script for building the Linear Algebra Library

# Exit immediately if a command exits with a non-zero status
set -e

echo "------------------------------------------"
echo "Cleaning old build files..."
make clean

echo "Building library components..."
make vector.o
make SparseMatrix.o
make cfd.o

echo "Creating the static library (libLinearAlgebra.a)..."
make libLinearAlgebra.a

echo "Compiling and linking the test suite (main)..."
make main

echo "------------------------------------------"
echo "Build Successful! Running Verification Test..."
echo "------------------------------------------"
./
