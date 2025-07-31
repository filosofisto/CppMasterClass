cmake_minimum_required(VERSION 3.20)
project(SharedCMakeB)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GNUInstallDirs once at root
include(GNUInstallDirs)   

add_subdirectory(math)
add_subdirectory(app)

