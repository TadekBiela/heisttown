add_subdirectory(Tests)

find_package(Qt6 COMPONENTS Core Multimedia REQUIRED)

set(LIB_NAME FilesStorage)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Core )
target_link_libraries(${LIB_NAME} PRIVATE Qt6::Multimedia )

target_include_directories(${LIB_NAME} INTERFACE .)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
