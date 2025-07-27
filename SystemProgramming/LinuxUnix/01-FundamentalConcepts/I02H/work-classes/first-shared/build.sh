#!/bin/bash

echo "Compiling library artifacts..."
g++ -fPIC -c math/add_vector.cpp -o build/add_vector.o
g++ -fPIC -c math/sub_vector.cpp -o build/sub_vector.o

echo "Create the shared library file (.so)..."
g++ -shared -o build/libhypernex_math.so build/add_vector.o build/sub_vector.o

echo "Build App..."
g++ app/main.cpp -Imath -Lbuild -lhypernex_math -o build/app -Wl,-rpath=./

echo "Done!"

