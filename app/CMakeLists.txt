add_custom_target(app)

set(PROJECT_NAME heisttown)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Multimedia Network)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Multimedia Qt6::Network)

add_dependencies(app ${PROJECT_NAME})
