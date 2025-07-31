add_executable(app main.cpp)
target_link_libraries(app PRIVATE hypernex_math)

#install(TARGETS app DESTINATION bin)
install(TARGETS app DESTINATION ${CMAKE_INSTALL_BINDIR}) # Portable bin install dir

# Ensure RPATH is embedded
set_target_properties(app PROPERTIES
	BUILD_WITH_INSTALL_RPATH TRUE
	INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

