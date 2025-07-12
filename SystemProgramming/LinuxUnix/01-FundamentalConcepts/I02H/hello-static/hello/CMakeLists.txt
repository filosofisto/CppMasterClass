add_library(hello STATIC
	hello.cpp
	hello.h
)

target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

