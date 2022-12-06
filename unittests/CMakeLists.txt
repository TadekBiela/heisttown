if(UNIX)
  set(EXEC_COMMAND ${CMAKE_BINARY_DIR}/tests/ut)
else()
  set(EXEC_COMMAND ${CMAKE_BINARY_DIR}/tests/ut.exe)

add_custom_target(buildut)
add_custom_target(runut COMMAND exec ${EXEC_COMMAND})

set(PROJECT_NAME ut)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Multimedia Network)
find_package(Qt6Test REQUIRED)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Multimedia Qt6::Network Qt6::Test)

add_dependencies(buildut ${PROJECT_NAME})
add_dependencies(runut ${PROJECT_NAME})

