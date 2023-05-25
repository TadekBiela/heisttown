add_subdirectory(MouseCursor)

find_package(Qt6 COMPONENTS Core Widgets Gui Multimedia Network REQUIRED)

set(LIB_NAME Client)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${LIB_NAME} PUBLIC HeistTown)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
