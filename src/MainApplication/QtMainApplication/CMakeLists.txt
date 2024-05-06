add_subdirectory(Tests)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(LIB_NAME QtMainApplication)

file(GLOB HEADER_FILES *.h)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(${LIB_NAME} PRIVATE MainApplication)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
