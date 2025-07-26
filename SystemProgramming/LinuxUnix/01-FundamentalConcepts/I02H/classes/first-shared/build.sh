#!/bin/bash

echo "Compiling library artifacts..."
g++ -fPIC -c math/add_vector.cpp -o build/add_vector.o
g++ -fPIC -c math/sub_vector.cpp -o build/sub_vector.o

echo "Create the shared library file (.so)..."
g++ -shared -o build/libhypernex_math.so build/add_vector.o build/sub_vector.o

echo "Build App..."
g++ app/main.cpp -Imath -Lbuild -lhypernex_math -o build/app -Wl,-rpath=./

# If ommit -Wl,-rpath then to execute the app we need to do it with the bellow command:
# LD_LIBRARY_PATH=./build ./build/app
# -Wl, : means pass the next options to the linker (ld)
# -rpath : This tells the linker to embed a runtime search path inside the executable
#          At runtime, the dynamic linker (ld-linux) uses this path to look for .so files before using default locations (like /usr/lib).
echo "Done!"

