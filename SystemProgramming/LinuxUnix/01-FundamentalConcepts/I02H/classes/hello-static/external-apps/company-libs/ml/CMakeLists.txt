cmake_minimum_required(VERSION 3.20)
project(ml VERSION 1.0 LANGUAGES CXX)

# Find math library
find_package(math REQUIRED PATHS ${CMAKE_PREFIX_PATH})

add_library(ml STATIC src/ml.cpp)

target_include_directories(ml PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(ml PUBLIC hypernex::math)

include(CMakePackageConfigHelpers)

install(TARGETS ml EXPORT mlTargets ARCHIVE DESTINATION lib)
install(FILES include/ml.h DESTINATION include)

install(EXPORT mlTargets
	FILE mlTargets.cmake
	NAMESPACE hypernex::
	DESTINATION cmake
)

configure_package_config_file(
	"${CMAKE_CURRENT_LIST_DIR}/cmake/mlConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/mlConfig.cmake"
	INSTALL_DESTINATION cmake/ml
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mlConfig.cmake" DESTINATION cmake)

