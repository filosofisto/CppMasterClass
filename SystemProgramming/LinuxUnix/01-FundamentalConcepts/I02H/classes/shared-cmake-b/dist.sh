#!/bin/bash

rm -rf build/ dist/

# -B build: the build directory
# -S . : the source directory
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=./dist

cmake --build build
cmake --install build


