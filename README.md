# Heist Town

**Heist Town** is a 2D sandbox multiplayer crime game — but more importantly, serves as a **demonstrator of robust C++ engineering practices**: unit testing, TDD, static/dynamic analysis, multi-threading, CI/CD, Docker-based cross-platform build and test infrastructure.

## 1. What this repository demonstrates

- Modern C++ development
- Use of a game framework (SFML) integrated into a testable architecture
- **Unit tests** covering the codebase, minimum 80% coverage
- **Multi-threaded code**, with concurrency tested
- Use of **Sanitizers, ThreadSanitizer, Valgrind** to catch memory/thread issues
- Code formatting & static checks: **ClangFormat + ClangTidy**
- Build and test environment based on **Docker** — ensures reproducibility and platform-agnostic setup
- **CMake** project setup, presets, and cross-platform support (Linux / Windows via Docker)
- Automated CI/CD via GitHub Actions

> This is not just a hobby game — it's a **proof-of-concept of engineering best practices in C++ projects**.


## 2. Why this matters from a professional standpoint
For potential employers / clients / collaborators, this repository shows that you:

Can handle modern C++ development with attention to quality and safety
Understand testing — not just unit tests, but thread-safety, memory safety, coverage, CI/CD
Can set up cross-platform, reproducible build & test pipelines (via Docker + CMake + CI)
Write maintainable, clean, and well-formatted code adhering to static analysis guidelines
Think about long-term maintenance, scalability and reproducibility


## 3. Contact & More (Your Info)
Feel free to reach out: tadek.biela@gmail.com
You can check my LinkedIn: https://www.linkedin.com/in/tadeuszbiela/
Or webside: https://cpptested.com/


## 4. License
This project is licensed under the GPL-3.0 License. See LICENSE for details.


## 5. How to build & run on Windows via Docker

### 5.1. Development using Linux Docker container

#### 5.1.1. Requirements

* Docker Desktop: https://www.docker.com/products/docker-desktop/ 
* VcXsrv Windows X Server: https://sourceforge.net/projects/vcxsrv/ 

#### 5.1.2. Prepare Project to Build

* Run VcXsrv Windows X Server with default configuration.
* Run command prompt ( `cmd` or `PowerShell` ) and check PC IP address using `ipconfig` command.
* Stay in command prompt and run Docker container using this command: \
`docker run --name heisttown -e DISPLAY=<your-pc-ip-address>:0 -it tadekbiela/heisttown:heisttown /bin/bash`

* `<your-pc-ip-address>` - put here you own PC IP address.
* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* You can stay in command prompt or move to Docker Desktop terminal.
* QtCreator is used as default IDE. You can run it using `qtcreator` command.

### 5.2. Development using Windows Docker container - only for terminal testing!

#### 5.2.1. Requirements

* Docker Desktop: https://www.docker.com/products/docker-desktop/ 

#### 5.2.2. Prepare Project to Build

* Switch Docker Desktop to Windows Container.
* Run command prompt ( `cmd` or `PowerShell` ) and run Docker container using this command: \
`docker run --name heisttown -it tadekbiela/heisttown:heisttown_win powershell`

* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* You can stay in command prompt or move to Docker Desktop terminal.


## 6 How to build & run on Linux via Docker

### 6.1. Requirements

* Docker: `sudo apt install -y docker.io`

### 6.2. Prepare Project to Build

* Run terminal and add all clients types to host using `xhost +` command.
* Run Docker container using this command: \
`sudo docker run --name heisttown -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -it tadekbiela/heisttown:heisttown /bin/bash`

* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* Next run `cmake --preset="Build"`
* QtCreator is used as default IDE. You can run it using `qtcreator &` command.
* Import project by `CmakeLists.txt`


## 7. Build Game Application

* To build game application, run this commands: \
`cmake .. && cmake --build . --target all`

* Game will be in `src/` folder as `HeistTown` file.


## 8. Build and Run Unit Tests

* To build unit tests as `ut` executable file, run this command: \
`cmake .. && cmake --build . --target all`

* To build and run all unit tests, use this command: \
`cmake .. && cmake --build . --target RunAllTests`

* To build and run all unit tests with Sanitizers, use this command: \
`cmake .. && cmake --build . --target Sanitizers`

* To build and run all unit tests with Valgrind, use this command: \
`cmake .. && cmake --build . --target Valgrind`

* To create code coverage report, use this command: \
`cmake .. && cmake --build . --target CodeCoverage`

* If you want run only one or part of unit tests you can use `gtest_filter`: \
`for example: \
	src/client/mousecursor/tests/MouseCursorTests --gtest_filter="*Default*"`
