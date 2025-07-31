# Static Library using CMake

This scenario is used when you have a library being produced inside the build pipeline of the project.

## Initialize 

    cmake -S . -B build

    S: Source directory
    B: Build directory

Execute this command on the first time or in these situations:

    You change CMake configuration, such as:
        - modifying CMakeLists.txt files (e.g., adding libraries, targets, include paths),
        - changing compiler options (e.g., CMAKE_CXX_STANDARD, CMAKE_BUILD_TYPE),
        - adding new source files that need to be included in targets.

    You delete or clean the build/ directory.

    You want to change generator options, like switching from Ninja to Makefiles, or changing build type (Debug/Release) using -DCMAKE_BUILD_TYPE=....

## Build

    cmake --build build

