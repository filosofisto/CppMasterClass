cmake_minimum_required(VERSION 3.20)
project(app LANGUAGES CXX)

# find_package(math REQUIRED) -> bring transitively
find_package(ml REQUIRED)

add_executable(app src/main.cpp)

target_link_libraries(app
	PRIVATE
	hypernex::ml
)

