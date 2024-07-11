if(NOT RELEASE)
    add_subdirectory(Tests)
endif()

set(LIB_NAME FilesStorage)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)
