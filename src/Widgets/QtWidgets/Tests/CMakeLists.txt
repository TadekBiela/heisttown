find_package(GTest REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(TEST_NAME QtWidgetsTests)

file(GLOB HEADER_FILES *.hpp)
aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${HEADER_FILES} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${TEST_NAME} PRIVATE Widgets)
target_link_libraries(${TEST_NAME} PRIVATE QtWidgets)

add_test(NAME ${TEST_NAME}
         COMMAND ${TEST_NAME})
