add_subdirectory(Client)
add_subdirectory(FilesStorage)
add_subdirectory(GameDisplay)
add_subdirectory(Keyboard)
add_subdirectory(MainApplication)
add_subdirectory(Menu)
add_subdirectory(MouseCursor)
add_subdirectory(PlayerInput)
add_subdirectory(Widgets)

set(PROJECT_NAME app LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Widgets Gui Multimedia Network REQUIRED)

set(APP_NAME HeistTown)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Multimedia Qt6::Network)
target_link_libraries(${APP_NAME} PRIVATE Client)
target_link_libraries(${APP_NAME} PRIVATE FilesStorage)
target_link_libraries(${APP_NAME} PRIVATE GameDisplay)
target_link_libraries(${APP_NAME} PRIVATE QtGameDisplay)
target_link_libraries(${APP_NAME} PRIVATE Keyboard)
target_link_libraries(${APP_NAME} PRIVATE MainApplication)
target_link_libraries(${APP_NAME} PRIVATE Menu)
target_link_libraries(${APP_NAME} PRIVATE PlayerInput)
target_link_libraries(${APP_NAME} PRIVATE Widgets)
target_link_libraries(${APP_NAME} PRIVATE QtWidgets)

set_target_properties(${APP_NAME} PROPERTIES AUTOMOC ON)
