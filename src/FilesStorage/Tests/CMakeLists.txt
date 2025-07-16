find_package(GTest REQUIRED)

set(TEST_NAME FilesStorageTests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.hpp")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_executable(${TEST_NAME} ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${TEST_NAME}
    PRIVATE
        GTest::gmock_main
        FilesStorage
)

add_test(NAME ${TEST_NAME}
         COMMAND ${TEST_NAME})
