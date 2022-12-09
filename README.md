# Heist Town
Heist Town it is 2D sandbox multiplayer crime game inspired by GTA 2.

## 1. Developing environment

* I prepared a Docker Image and it is available on Docker Hub public repository: `tadekbiela/heisttown:heisttown`
* This image contains all needed dependencies to develop, run and test the project.
* To run game on Windows using Docker Image first you need to install VcXsrv Windows X Server: \
https://sourceforge.net/projects/vcxsrv/
* After installation you need to run it.
* Check your PC IP address in CMD using `ipconfig` command.
* When you prepare preconditions you can run in PowerShell terminal this command to run Docker( in the place where is `192.168.0.164` you need paste your PC IP address): \
`docker run --name heisttown -e DISPLAY=192.168.0.164:0 --expose 3000 -p 3000:3000 -v //c/Users/TED/Desktop:/src -t -i tadekbiela/heisttown:heisttown /bin/bash`
* Do not forget pull all changes: 
`git pull`
* **Enjoy!**
