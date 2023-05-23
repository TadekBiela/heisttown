cmake_minimum_required(VERSION 3.22)
project("Heist Town" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(BUILD_SHARED_LIBS OFF)

if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

set(CMAKE_DEBUG_POSTFIX d)

enable_testing()

add_subdirectory(app)

add_custom_target(RunAllTests
        COMMAND "${CMAKE_COMMAND}" --build . --target all
        COMMAND "${CMAKE_COMMAND}" --build . --target test
        COMMENT "Running tests"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)
