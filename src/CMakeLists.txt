add_subdirectory(Client)
add_subdirectory(FilesStorage)
add_subdirectory(GameDisplay)
add_subdirectory(MainApplication)
add_subdirectory(Menu)
add_subdirectory(MouseCursor)
add_subdirectory(PlayerInput)
add_subdirectory(Server)
add_subdirectory(Widgets)

set(APP_NAME HeistTown)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_executable(${APP_NAME} MACOSX_BUNDLE ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${APP_NAME}
    PRIVATE
        Client
        FilesStorage
        GameDisplay
        MainApplication
        Menu
        PlayerInput
        Server
        Widgets
)
