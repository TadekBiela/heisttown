find_package(GTest REQUIRED)

set(TEST_NAME MenuTests)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${HEADER_FILES} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_NAME} PRIVATE FilesStorage)
target_link_libraries(${TEST_NAME} PRIVATE MainControl)
target_link_libraries(${TEST_NAME} PRIVATE Menu)
target_link_libraries(${TEST_NAME} PRIVATE Widgets)

add_test(NAME ${TEST_NAME}
	 COMMAND ${TEST_NAME})
