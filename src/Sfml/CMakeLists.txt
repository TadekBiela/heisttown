if(NOT RELEASE)
    add_subdirectory(Tests)
endif()

add_subdirectory(SfmlInput)
add_subdirectory(SfmlRendering)
add_subdirectory(SfmlWidgets)

set(LIB_NAME Sfml)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    PUBLIC
        FilesStorage
        Input
        Rendering
        Scene
        SfmlInput
        SfmlRendering
        sfml-graphics
        sfml-window
        sfml-system
)
