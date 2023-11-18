cmake_minimum_required(VERSION 3.22)
project("Heist Town" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)

option(SANITIZE "Enable sanitizers" OFF)
option(THREAD_SANITIZE "Enable thread sanitizers" OFF)
option(VALGRIND "Enable valgrind" OFF)
option(RELEASE "Build release" OFF)
option(CODE_COVERAGE "Enable code coverage" OFF)
option(CLANG_TIDY "Enable clang-tidy" OFF)

set(COMMON_COMPILE_FLAGS " -Wall -Wextra -Werror -Wdouble-promotion -Wmisleading-indentation ")
set(COMPILE_FLAGS "")

if(SANITIZE)
    message(STATUS "Configuring Sanitizers")
    set(COMPILE_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -g -fno-omit-frame-pointer \
        -fsanitize=address \
        -fsanitize=undefined \
        -fsanitize=pointer-compare \
        -fsanitize=leak")
elseif(THREAD_SANITIZE)
    message(STATUS "Configuring Thread Sanitizers")
    set(COMPILE_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -g -fno-omit-frame-pointer \
        -fsanitize=thread \
        -fsanitize=undefined")
elseif(VALGRIND)
    find_program(VALGRIND_EXECUTABLE valgrind)
    if(VALGRIND_EXECUTABLE)
        message(STATUS "Valgrind found: ${VALGRIND_EXECUTABLE}")
        message(STATUS "Configuring Valgrind")
        set(COMPILE_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
    else()
        message(WARNING "Valgrind not found")
    endif()
elseif(RELEASE)
    message(STATUS "Configuring Release")
    set(COMPILE_FLAGS " -O2 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
elseif(CODE_COVERAGE)
    message(STATUS "Configuring Code Coverage")
    set(COMPILE_FLAGS " -O0 -g --coverage -fprofile-arcs -ftest-coverage")
elseif(CLANG_TIDY)
    message(STATUS "Configuring Clang-Tidy")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
else()
    message(STATUS "Configuring Debug")
    set(COMPILE_FLAGS " -O0 ${COMMON_COMPILE_FLAGS} -Wnull-dereference")
endif()

string(APPEND CMAKE_C_FLAGS "${COMPILE_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS "${COMPILE_FLAGS}")
string(APPEND CMAKE_EXE_LINKER_FLAGS "${COMPILE_FLAGS}")
message(STATUS "Seted compile flags: ${CMAKE_CXX_FLAGS}")

set(BUILD_SHARED_LIBS OFF)

if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()

set(CMAKE_DEBUG_POSTFIX d)

enable_testing()

add_subdirectory(src)

add_custom_target(RunAllTests
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D VALGRIND=OFF -D RELEASE=OFF ..
    COMMAND "${CMAKE_COMMAND}" --build . --target all
    COMMAND "${CMAKE_COMMAND}" --build . --target test
    COMMENT "Running tests"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

add_custom_target(Sanitizers
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=ON ..
    COMMAND "${CMAKE_COMMAND}" --build .
    COMMAND "${CMAKE_CTEST_COMMAND}" --verbose
    COMMENT "Running Sanitizers"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

add_custom_target(ThreadSanitizers
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D THREAD_SANITIZE=ON ..
    COMMAND "${CMAKE_COMMAND}" --build .
    COMMAND "${CMAKE_CTEST_COMMAND}" --verbose
    COMMENT "Running Thread Sanitizers"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--leak-check=yes --show-reachable=yes --track-origins=yes --xtree-leak=yes --error-exitcode=1")
add_custom_target(Valgrind
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D THREAD_SANITIZE=OFF -D VALGRIND=ON ..
    COMMAND "${CMAKE_COMMAND}" --build .
    COMMAND "${CMAKE_CTEST_COMMAND}" --verbose --overwrite MemoryCheckCommandOptions=${CTEST_MEMORYCHECK_COMMAND_OPTIONS} -T memcheck
    COMMENT "Running Valgrind"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

add_custom_target(Release
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D THREAD_SANITIZE=OFF -D VALGRIND=OFF -D RELEASE=ON ..
    COMMAND "${CMAKE_COMMAND}" --build . --target all
    COMMENT "Running Relese"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

set(COVERAGE_LEVEL "80")
add_custom_target(CodeCoverage
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D THREAD_SANITIZE=OFF -D VALGRIND=OFF -D RELEASE=OFF -D CODE_COVERAGE=ON ..
    COMMAND "${CMAKE_COMMAND}" --build . --target all
    COMMAND "${CMAKE_CTEST_COMMAND}"
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND lcov --extract coverage.info "/usr/src/heisttown/src/*" -o coverage_filtered.info
    COMMAND lcov --list coverage_filtered.info
    COMMAND lcov --list coverage_filtered.info | grep Total:*.*% | grep -o .[0-9].[0-9]% | grep -o .[0-9].[0-9] > coverage_level.txt
    COMMAND sh -c " awk '{ for (i=1; i<=NF; i++) { if ($i < ${COVERAGE_LEVEL}) { print \"Coverage level is to low! Required minimum ${COVERAGE_LEVEL}%\"; exit 1 } } }' coverage_level.txt"
    COMMENT "Running Code Coverage"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

add_custom_target(ClangTidy
    COMMAND "${CMAKE_COMMAND}" -D SANITIZE=OFF -D THREAD_SANITIZE=OFF -D VALGRIND=OFF -D RELEASE=OFF -D CODE_COVERAGE=OFF -D CLANG_TIDY=ON ..
    COMMAND "${CMAKE_COMMAND}" --build . --target all
    COMMENT "Running Clang-Tidy"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM)

add_custom_target(ClangFormat
    COMMAND find src/ -name "*.cpp" -o -name "*.h" | xargs clang-format -i -style=file
    COMMENT "Running clang-format on source files"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    VERBATIM)
