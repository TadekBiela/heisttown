# Build commands

### 1. Build Game Application

* To build game application, run this commands: \
`cmake ../ && make -j app`

* Game will be in `app/` folder as `heisttown` file.

### 2. Build and Run Unit Tests

* To build unit tests as `ut` executable file, run this command: \
`cmake ../ && make -j buildut`

* To build and run all unit tests, use this command: \
`cmake ../ && make -j runut`

* If you want run only one or part of unit tests you can use `gtest_filter`: \
`cmake ../ && make -j buildut && unittests/ut --gtest_filter="*Client*"`


