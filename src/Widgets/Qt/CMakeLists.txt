add_subdirectory(Tests)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(LIB_NAME Qt)

file(GLOB HEADER_FILES *.h)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${LIB_NAME} PRIVATE Widgets)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
