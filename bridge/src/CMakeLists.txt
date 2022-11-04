set(SOURCE_FILES
	daemon.cpp
	i2c.cpp
	process_lock.cpp

	network/controller.cpp)

set(HEADER_FILES
	${BRIDGE_INCLUDE_DIR}/bridge/daemon.h
	${BRIDGE_INCLUDE_DIR}/bridge/i2c.h
	${BRIDGE_INCLUDE_DIR}/bridge/process_lock.h
	${BRIDGE_INCLUDE_DIR}/bridge/std_lib.h

	${BRIDGE_INCLUDE_DIR}/bridge/network/controller.h)

# Make an automatic library - will be static or dynamic based on user setting
add_library(bridge_lib ${SOURCE_FILES} ${HEADER_FILES})

# Targets depending on this library will need at least C++17
target_compile_features(bridge_lib PUBLIC cxx_std_17)

# Add all needed header files. Users of this library will need them too
target_include_directories(bridge_lib
	PUBLIC
		${BRIDGE_INCLUDE_DIR}
		spdlog::spdlog)

# Link with necessary libraries
target_link_libraries(bridge_lib
	PUBLIC
		spdlog::spdlog
	PRIVATE
		systemd)

# Nicely group source and header files in IDEs that support this
source_group(TREE "${PROJECT_SOURCE_DIR}/src" FILES ${SOURCE_FILES})
source_group(TREE "${PROJECT_SOURCE_DIR}/include" FILES ${HEADER_FILES})