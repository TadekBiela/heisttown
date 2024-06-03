add_subdirectory(Tests)

set(LIB_NAME Client)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE GameDisplay)
target_link_libraries(${LIB_NAME} PRIVATE PlayerInput)
