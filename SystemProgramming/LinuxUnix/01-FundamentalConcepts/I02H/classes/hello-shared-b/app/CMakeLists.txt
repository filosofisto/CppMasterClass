add_executable(app main.cpp)
target_link_libraries(app PRIVATE hello)

#set_target_properties(app PROPERTIES
#	INSTALL_RPATH "$ORIGIN/../lib"
#)

install(TARGETS app DESTINATION bin)

# Ensure RPATH is embedded
set_target_properties(app PROPERTIES
	BUILD_WITH_INSTALL_RPATH TRUE
	INSTALL_RPATH "$ORIGIN/../lib"
)



