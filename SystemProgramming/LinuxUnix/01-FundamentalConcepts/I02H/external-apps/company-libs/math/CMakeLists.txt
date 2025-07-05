cmake_minimum_required(VERSION 3.20)
project(math VERSION 1.0 LANGUAGES CXX)

add_library(math STATIC src/math.cpp)

target_include_directories(math PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# Exported namespace will be: hypernex::math
include(CMakePackageConfigHelpers)

install(TARGETS math EXPORT mathTargets ARCHIVE DESTINATION lib)
install(FILES include/math.h DESTINATION include)

install(EXPORT mathTargets
	FILE mathTargets.cmake
	NAMESPACE hypernex::
	DESTINATION cmake
)

configure_package_config_file(
	"${CMAKE_CURRENT_LIST_DIR}/cmake/mathConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake"
	INSTALL_DESTINATION cmake/math
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mathConfig.cmake" DESTINATION cmake)


