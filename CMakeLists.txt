cmake_minimum_required(VERSION 3.28)
project(OGLEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

add_executable(game)
add_library(oglengine STATIC)

if(MSVC)
    target_link_options(oglengine PRIVATE "/NODEFAULTLIB:MSVCRT")
    target_link_options(game PRIVATE "/NODEFAULTLIB:MSVCRT")
endif()

# Library options
file(GLOB_RECURSE SRC_FILES "src/*.c*")
target_sources(oglengine PRIVATE ${SRC_FILES})
target_include_directories(oglengine PRIVATE "include" ${ASSIMP_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(oglengine PRIVATE ${ASSIMP_LIBRARY_RELEASE} ${GLFW3_LIBRARY} OpenGL::GL)

# Game options
file(GLOB_RECURSE EXAMPLE_SRC_FILES "example/*.cpp")
target_sources(game PRIVATE ${EXAMPLE_SRC_FILES})
target_include_directories(game PRIVATE "include" ${ASSIMP_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(game PRIVATE ${ASSIMP_LIBRARY_RELEASE} ${GLFW3_LIBRARY} OpenGL::GL oglengine)
