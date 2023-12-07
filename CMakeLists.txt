cmake_minimum_required(VERSION 3.28)
project(OGLEngine)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# Find the GLFW package
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add the executable
add_executable(game)
add_library(oglengine STATIC)

# Add all *.cpp files in the src directory to a variable
file(GLOB_RECURSE SRC_FILES "src/*.c*")

# Set the source files for the executable
target_sources(oglengine PRIVATE ${SRC_FILES})

target_include_directories(oglengine PRIVATE "include" ${GLFW3_INCLUDE_DIR})

# Link against the GLFW library
target_link_libraries(oglengine PRIVATE ${GLFW3_LIBRARY} OpenGL::GL)

# Add all *.cpp files in the src directory to a variable
file(GLOB_RECURSE EXAMPLE_SRC_FILES "example/*.cpp")

# Set the source files for the executable
target_sources(game PRIVATE ${EXAMPLE_SRC_FILES})

target_include_directories(game PRIVATE "include" ${GLFW3_INCLUDE_DIR})

# Link against the GLFW library
target_link_libraries(game PRIVATE ${GLFW3_LIBRARY} OpenGL::GL oglengine)
