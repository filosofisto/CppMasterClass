# Static Library Manual Approach

## Commands

### Compile the artfacts cpp and build the static library (.a):

    g++ -c math/add_vector.cpp build/add_vector.o
    g++ -c math/sub_vector.cpp build/sub_vector.o
    ar rcs build/libhypernex_math.a build/add_vector.o build/sub_vector.o

    r: replace existing or insert new file(s) into the archive
    c: do not warn if the library had to be created
    s: create an archive index (cf. ranlib).

    The symbol table (index) lets the linker quickly find symbols inside the archive.
    Without the s option, the linker might have to scan the entire archive, which is slower or can fail to find needed symbols.
    Running ar without s might require you to run ranlib afterward to generate the symbol table.

### Build App (app):

    g++ app/main.cpp -Imath -Lbuild -lhypernex_math -o build/app

    -Lbuild: When linking, also look in the build/ folder for libraries
    -lhypernex_math: Link with a library named libhypernex_math.a (static) or libhipernext_math.so (shared), depending on what is available.

    -o build/app: Output file

### Utilities

List all symbols from an executable.

    nm app | grep add_vector # will show that the function add_vector is present
    nm app | grep sub_vector # will show that the function sub_vector is NOT present


