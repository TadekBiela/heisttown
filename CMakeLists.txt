cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++17 -g")
set(BUILD_SHARED_LIBS OFF)

project("Heist Town")
enable_testing()

add_subdirectory(app)
add_subdirectory(unittests)
