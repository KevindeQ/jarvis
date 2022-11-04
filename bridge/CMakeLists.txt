cmake_minimum_required (VERSION 3.19)

project(
  bridge
  VERSION 0.1
  LANGUAGES CXX)

# Only do this when this is the main project
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)

  # Enable support for folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Disable the use of c++ compiler extensions
  set(CXX_EXTENSIONS OFF)

endif()

set(BRIDGE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/spdlog)
#find_package(spdlog)

add_subdirectory(src)
add_subdirectory(apps)
