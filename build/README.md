#Build commands

## 1. Build game
  * Run this commands combination to build game as `heisttown` file in Git Bash console: \
      `cmake ../ -G "Unix Makefiles" && make -j4 app`

  * Game `heisttown` file is in `app/` folder. **Enjoy!**


## 2. Build and run Unit Tests
  * Run this commands combination to build Unit Tests as `ut` file: \
      `cmake ../ -G "Unix Makefiles" && make -j4 buildut`

  * If you want run only one or part of UTs just use `gtest_filter`: \
      `cmake ../ -G "Unix Makefiles" && make -j4 buildut && tests/ut --gtest_filter="*Client*"`

  * If you want build and run Uts use this command: \
      `cmake ../ -G "Unix Makefiles" && make -j4 runut`


