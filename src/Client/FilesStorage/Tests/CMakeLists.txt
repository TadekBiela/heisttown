find_package(Qt6 COMPONENTS Core Multimedia REQUIRED)
find_package(GTest REQUIRED)

set(TEST_NAME FilesStorageTests)

aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE Qt6::Core)
target_link_libraries(${TEST_NAME} PRIVATE Qt6::Multimedia)
target_link_libraries(${TEST_NAME} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_NAME} PRIVATE FilesStorage)

add_test(NAME ${TEST_NAME}
         COMMAND ${TEST_NAME})
