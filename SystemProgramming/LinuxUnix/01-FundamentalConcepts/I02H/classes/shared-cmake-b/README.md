# Hello Library

## Scenario

- Shared library
- Used when you have a library being produced inside the build pipeline of the project
- It produce a folder dist for distribute the solution as:

    dist/
        bin/
            app
        include/
            hello.h
        lib/
            libhello.so

    This is one of best way to distribute an application with its libraries.

## Some Explanations

    include(GNUInstallDirs)

        This is a CMake built-in module you include in your CMakeLists.txt.

        It defines a set of standard variables for installation directories that follow the GNU/Linux Filesystem Hierarchy Standard (FHS) and common conventions.

        These variables include:
        Variable	             Typical Value	Usage
        CMAKE_INSTALL_BINDIR	 bin	        Executable binaries
        CMAKE_INSTALL_LIBDIR	 lib or lib64	Shared libraries (.so, .dll)
        CMAKE_INSTALL_INCLUDEDIR	            include	Header files
        CMAKE_INSTALL_DATADIR	 share	        Architecture-independent data

        Using these variables instead of hardcoding paths like "lib" or "include" makes your project:

            Portable: Automatically adapts to the target system’s conventions.
            Clean: Avoids magic strings in your CMake files.
            Package-friendly: Packages your software in a way Linux distros expect.
    --

    target_include_directories(hipernex_math PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
    )

        This command tells CMake where to find header files when building and when consuming the library.

        Key parts:
        Part	                    Meaning
        target_include_directories	Defines include paths for a given target (hipernex_math)
        PUBLIC	                    Include dirs are added to this target and to anything that links to it
        $<BUILD_INTERFACE:...>	    During build (when you compile your project locally), use this path for includes
        $<INSTALL_INTERFACE:...>	After install (when someone uses your installed library), use this path for includes

        How it works in your project:

            When building your library or your app locally:
                ${CMAKE_CURRENT_SOURCE_DIR}  → the `math/` folder containing the headers like `hypernex_math.h`
            When installed and used by others:
                include/   → the folder where the header file is installed (e.g. `./dist/include/hypernex_math.h)
