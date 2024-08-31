cmake_minimum_required(VERSION 3.16)

project(Date LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Date main.cpp
    date.h date.cpp)

include(GNUInstallDirs)
install(TARGETS Date
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
