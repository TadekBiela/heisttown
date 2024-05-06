add_subdirectory(QtWidgets)

find_package(GTest REQUIRED)

set(LIB_NAME Widgets)

file(GLOB HEADER_FILES *.h)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
