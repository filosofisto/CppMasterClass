#!/bin/bash

echo "Compiling library artifacts..."
g++ -c math/add_vector.cpp -o build/add_vector.o
g++ -c math/sub_vector.cpp -o build/sub_vector.o

echo "Create the static library file (.a)..."
ar rs build/libhypernex_math.a build/add_vector.o build/sub_vector.o

echo "Build App..."
g++ app/main.cpp -Imath -Lbuild -lhypernex_math -o build/app

echo "Done!"

