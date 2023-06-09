# Heist Town

Heist Town is a 2D sandbox multiplayer crime game inspired by GTA 2.

## 1. Windows development

### 1.1 Development using Linux Docker container

#### 1.1.1. Requirements

* Docker Desktop: https://www.docker.com/products/docker-desktop/ 
* VcXsrv Windows X Server: https://sourceforge.net/projects/vcxsrv/ 

#### 1.1.2 Prepare Project to Build

* Run VcXsrv Windows X Server with default configuration.
* Run command prompt ( `cmd` or `PowerShell` ) and check PC IP address using `ipconfig` command.
* Stay in command prompt and run Docker container using this command: \
`docker run --name heisttown -e DISPLAY=<your-pc-ip-address>:0 -it tadekbiela/heisttown:heisttown /bin/bash`

* `<your-pc-ip-address>` - put here you own PC IP address.
* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* You can stay in command prompt or move to Docker Desktop terminal.
* QtCreator is used as default IDE. You can run it using `qtcreator` command.

### 1.2 Development using Windows Docker container - only for terminal testing!

#### 1.2.1. Requirements

* Docker Desktop: https://www.docker.com/products/docker-desktop/ 

#### 1.2.2 Prepare Project to Build

* Switch Docker Desktop to Windows Container.
* Run command prompt ( `cmd` or `PowerShell` ) and run Docker container using this command: \
`docker run --name heisttown -it tadekbiela/heisttown:heisttown_win powershell`

* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* You can stay in command prompt or move to Docker Desktop terminal.

## 2. Linux development

### 2.1 Requirements

* Docker: `sudo apt install -y docker.io`

### 2.2. Prepare Project to Build

* Run terminal and add all clients types to host using `xhost +` command.
* Run Docker container using this command: \
`sudo docker run --name heisttown -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -it tadekbiela/heisttown:heisttown /bin/bash`

* When Docker container will run, do not forget to pull all new changes using `git pull` command.
* QtCreator is used as default IDE. You can run it using `qtcreator` command.

## 3. Build Game Application

* To build game application, run this commands: \
`cmake .. && cmake --build . --target all`

* Game will be in `src/` folder as `HeistTown` file.

## 4. Build and Run Unit Tests

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
