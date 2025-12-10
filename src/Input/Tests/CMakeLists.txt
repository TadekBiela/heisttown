find_package(GTest REQUIRED)

set(TEST_NAME InputTests)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_executable(${TEST_NAME} ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${TEST_NAME}
    PRIVATE
        GTest::gmock_main
        Input
)

add_test(NAME ${TEST_NAME}
         COMMAND ${TEST_NAME})
