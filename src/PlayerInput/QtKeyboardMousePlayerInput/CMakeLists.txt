find_package(Qt6 COMPONENTS Core Gui REQUIRED)

set(LIB_NAME QtKeyboardMousePlayerInput)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Core Qt6::Gui)
target_link_libraries(${LIB_NAME} PRIVATE PlayerInput)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)
