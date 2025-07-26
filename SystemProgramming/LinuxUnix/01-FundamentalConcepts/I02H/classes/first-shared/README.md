# Shared Library Manual Approach

## Commands

### Compile the artfacts cpp and build the shared library (.so):

    g++ -fPIC -c math/add_vector.cpp build/add_vector.o
    g++ -fPIC -c math/sub_vector.cpp build/sub_vector.o
    g++ -shared -o build/libhypernex_math.so build/add_vector.o build/sub_vector.o

PIC: Position Independent Code
ELF: Executable and Linkable Format
     It’s the standard binary format for executables, object files, shared libraries (.so), and core dumps on Unix-like systems (Linux, BSD, etc.)

### Build App (app):

    g++ app/main.cpp -Imath -Lbuild -lhypernex_math -o build/app -Wl,-rpath=./build

    -Lbuild: When linking, also look in the build/ folder for libraries
    -lhypernex_math: Link with a library named libhypernex_math.a (static) or libhipernext_math.so (shared), depending on what is available.
    -o build/app: Output file

If ommit -Wl,-rpath then to execute the app we need to do it with the bellow command:
    LD_LIBRARY_PATH=./build ./build/app
-Wl, : means pass the next options to the linker (ld)
-rpath : This tells the linker to embed a runtime search path inside the executable          
         At runtime, the dynamic linker (ld-linux) uses this path to look for .so files before using default locations (like /usr/lib).

If you place your .so in one of these folders, it will always be found:

    /lib
    /usr/lib
    /lib64
    /usr/lib64
    /usr/local/lib (common for user-installed libraries)

After placing your .so there, you may also need to run:

    sudo ldconfig

This updates the linker’s cache (/etc/ld.so.cache) so it includes the new library.

### Utility
    
    ldd app
    // To show the reference to the library

    file libhypernex_math.so
    // libhypernex_math.so: ELF 64-bit LSB shared object, ARM aarch64, version 1 (SYSV), dynamically linked, BuildID[sha1]=d9d66a0c232afd3fd1cac79cbaedd6bea8355e64, not stripped

    readelf -h libhypernex_math.so
    ELF Header:
        Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
        Class:                             ELF64
        Data:                              2's complement, little endian
        Version:                           1 (current)
        OS/ABI:                            UNIX - System V
        ABI Version:                       0
        Type:                              DYN (Shared object file)
        Machine:                           AArch64
        Version:                           0x1
        Entry point address:               0x0
        Start of program headers:          64 (bytes into file)
        Start of section headers:          69320 (bytes into file)
        Flags:                             0x0
        Size of this header:               64 (bytes)
        Size of program headers:           56 (bytes)
        Number of program headers:         7
        Size of section headers:           64 (bytes)
        Number of section headers:         28
        Section header string table index: 27

    readelf -d build/app
    // It will list dynamic section entries, confirming it's dynamically linkable (which static libraries don't have)
