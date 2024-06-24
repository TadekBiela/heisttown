add_subdirectory(Tests)

set(LIB_NAME MainApplication)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Client)
target_link_libraries(${LIB_NAME} PRIVATE MainControl)
target_link_libraries(${LIB_NAME} PRIVATE Menu)
target_link_libraries(${LIB_NAME} PRIVATE PlayerInput)
target_link_libraries(${LIB_NAME} PRIVATE Widgets)
