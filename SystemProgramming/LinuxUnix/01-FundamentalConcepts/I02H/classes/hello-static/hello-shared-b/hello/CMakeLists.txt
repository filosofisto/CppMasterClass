add_library(hello SHARED
	hello.cpp
	hello.h
)

# Normal option
#target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Option distributing the application together the library
target_include_directories(hello PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

install(TARGETS hello
	LIBRARY DESTINATION lib
)

install(FILES hello.h DESTINATION include)

