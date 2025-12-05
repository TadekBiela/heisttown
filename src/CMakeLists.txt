add_subdirectory(Client)
add_subdirectory(FilesStorage)
add_subdirectory(Gameplay)
add_subdirectory(MainApplication)
add_subdirectory(Menu)
add_subdirectory(MouseCursor)
add_subdirectory(PlayerInput)
add_subdirectory(Server)
add_subdirectory(Sfml)
add_subdirectory(Widgets)

set(APP_NAME HeistTown)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Menus
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${APP_NAME} MACOSX_BUNDLE ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${APP_NAME}
    PRIVATE
        Client
        FilesStorage
        Gameplay
        MainApplication
        Menu
        PlayerInput
        Server
        Sfml
        SfmlWidgets
        Widgets
)
