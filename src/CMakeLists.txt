add_subdirectory(Client)
add_subdirectory(FilesStorage)
add_subdirectory(GameDisplay)
add_subdirectory(MainApplication)
add_subdirectory(MainControl)
add_subdirectory(Menu)
add_subdirectory(MouseCursor)
add_subdirectory(PlayerInput)
add_subdirectory(Server)
add_subdirectory(Widgets)

set(PROJECT_NAME app LANGUAGES CXX)

set(APP_NAME HeistTown)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE Client)
target_link_libraries(${APP_NAME} PRIVATE FilesStorage)
target_link_libraries(${APP_NAME} PRIVATE GameDisplay)
target_link_libraries(${APP_NAME} PRIVATE MainApplication)
target_link_libraries(${APP_NAME} PRIVATE MainControl)
target_link_libraries(${APP_NAME} PRIVATE Menu)
target_link_libraries(${APP_NAME} PRIVATE PlayerInput)
target_link_libraries(${APP_NAME} PRIVATE Server)
target_link_libraries(${APP_NAME} PRIVATE Widgets)

set_target_properties(${APP_NAME} PROPERTIES AUTOMOC ON)
