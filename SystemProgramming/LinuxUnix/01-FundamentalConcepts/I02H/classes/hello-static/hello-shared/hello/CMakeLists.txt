add_library(hello SHARED
	hello.cpp
	hello.h
)

target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

