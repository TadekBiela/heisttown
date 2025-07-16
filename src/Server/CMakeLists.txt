if(NOT RELEASE)
    add_subdirectory(Tests)
endif()

set(LIB_NAME Server)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    PUBLIC
        Client
        MainControl
        PlayerInput
)
