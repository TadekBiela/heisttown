if(NOT RELEASE)
    add_subdirectory(Tests)
endif()

set(LIB_NAME Sfml)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Font
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    PUBLIC
    Display
    Widgets
    sfml-graphics
    sfml-window
    sfml-system
)
