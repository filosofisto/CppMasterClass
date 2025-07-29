add_library(hypernex_math
	add_vector.cpp
	sub_vector.cpp
)

target_include_directories(hypernex_math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

