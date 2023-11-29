add_subdirectory(Tests)

find_package(Qt6 COMPONENTS Core Widgets Gui Multimedia Network REQUIRED)

set(LIB_NAME MouseCursor)

file(GLOB HEADER_FILES *.h)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${LIB_NAME} INTERFACE .)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
