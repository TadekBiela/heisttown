add_subdirectory(Client)
add_subdirectory(FilesStorage)
add_subdirectory(MainApplication)
add_subdirectory(Menu)
add_subdirectory(Widgets)

set(PROJECT_NAME app LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Widgets Gui Multimedia Network REQUIRED)

set(APP_NAME HeistTown)

aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Multimedia Qt6::Network)
target_link_libraries(${APP_NAME} PRIVATE FilesStorage)
target_link_libraries(${APP_NAME} PRIVATE Menu)
target_link_libraries(${APP_NAME} PRIVATE Widgets)
target_link_libraries(${APP_NAME} PRIVATE Qt)

set_target_properties(${APP_NAME} PROPERTIES AUTOMOC ON)
