add_library(hypernex_math SHARED
	add_vector.cpp
	sub_vector.cpp
)

# Option distributing the application together the library
target_include_directories(hypernex_math PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

install(TARGETS hypernex_math
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # Portable library install dir
)

install(FILES hypernex_math.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})  # Portable include dir
