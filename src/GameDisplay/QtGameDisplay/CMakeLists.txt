find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(LIB_NAME QtGameDisplay)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${LIB_NAME} PRIVATE GameDisplay)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
