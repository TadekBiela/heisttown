add_subdirectory(QtGameDisplay)

find_package(GTest REQUIRED)

set(LIB_NAME GameDisplay)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

