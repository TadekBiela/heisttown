cmake_minimum_required(VERSION 3.22)
project("Heist Town" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)

option(SANITIZE "Enable sanitizers" OFF)
option(VALGRIND "Enable valgrind" OFF)
option(RELEASE "Build Release" OFF)

set(COMMON_COMPILE_FLAGS " -Wall -Wextra -Werror -Wdouble-promotion -Wmisleading-indentation ")

if(SANITIZE)
    message(STATUS "Configuring Sanitizers")
    set(SANITIZE_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -g -fno-omit-frame-pointer \
        -fsanitize=address \
        -fsanitize=undefined \
        -fsanitize=shift \
        -fsanitize=integer-divide-by-zero \
        -fsanitize=vla-bound \
        -fsanitize=null \
        -fsanitize=return \
        -fsanitize=signed-integer-overflow \
        -fsanitize=bounds-strict \
        -fsanitize=float-divide-by-zero \
        -fsanitize=float-cast-overflow \
        -fsanitize=nonnull-attribute \
        -fsanitize=returns-nonnull-attribute \
        -fsanitize=enum \
        -fsanitize=vptr")
    string(APPEND CMAKE_C_FLAGS "${SANITIZE_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS "${SANITIZE_FLAGS}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS "${SANITIZE_FLAGS}")
elseif(VALGRIND)
    find_program(VALGRIND_EXECUTABLE valgrind)
    if(VALGRIND_EXECUTABLE)
        message(STATUS "Valgrind found: ${VALGRIND_EXECUTABLE}")
        message(STATUS "Configuring Valgrind")
        set(VALGRIND_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
        string(APPEND CMAKE_C_FLAGS "${VALGRIND_FLAGS}")
        string(APPEND CMAKE_CXX_FLAGS "${VALGRIND_FLAGS}")
        string(APPEND CMAKE_EXE_LINKER_FLAGS "${VALGRIND_FLAGS}")
    else()
        message(WARNING "Valgrind not found")
    endif()
elseif(RELEASE)
    set(RELEASE_FLAGS " -O2 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
    string(APPEND CMAKE_C_FLAGS "${RELEASE_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS "${RELEASE_FLAGS}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS "${RELEASE_FLAGS}")
else()
    set(DEBUG_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
    string(APPEND CMAKE_C_FLAGS "${DEBUG_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS "${DEBUG_FLAGS}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS "${DEBUG_FLAGS}")
endif()

message(STATUS "Setuped compile flags: ${CMAKE_CXX_FLAGS}")

set(BUILD_SHARED_LIBS OFF)

if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

set(CMAKE_DEBUG_POSTFIX d)

enable_testing()

add_subdirectory(src)

add_custom_target(RunAllTests
        COMMAND "${CMAKE_COMMAND}" --build . --target all
        COMMAND "${CMAKE_COMMAND}" --build . --target test
        COMMENT "Running tests"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)

add_custom_target(Sanitizers
        COMMAND "${CMAKE_COMMAND}" -D SANITIZE=ON -D VALGRIND=OFF -D RELEASE=OFF ..
        COMMAND "${CMAKE_COMMAND}" --build .
        COMMAND "${CMAKE_CTEST_COMMAND}" --verbose
        COMMENT "Running Sanitizers"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--leak-check=yes --show-reachable=yes --track-origins=yes --xtree-leak=yes --error-exitcode=1")
add_custom_target(Valgrind
        COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D VALGRIND=ON -D RELEASE=OFF ..
        COMMAND "${CMAKE_COMMAND}" --build .
        COMMAND "${CMAKE_CTEST_COMMAND}" --verbose --overwrite MemoryCheckCommandOptions=${CTEST_MEMORYCHECK_COMMAND_OPTIONS} -T memcheck
        COMMENT "Running Valgrind"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)

add_custom_target(Release
        COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D VALGRIND=OFF -D RELEASE=ON ..
        COMMAND "${CMAKE_COMMAND}" --build . --target all
        COMMENT "Running Valgrind"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)
