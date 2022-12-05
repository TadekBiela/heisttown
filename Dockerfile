# Get the Qt6 Google Test Ubuntu image from Docker Hub
FROM tadekbiela/cpp_development:qt6_gtest_cpp_image

# Clone heisttown repository
WORKDIR /usr/src
RUN git clone https://github.com/TadekBiela/heisttown.git

# Set to working directory and build heisttown
WORKDIR /usr/src/heisttown
RUN mkdir build
WORKDIR /usr/src/heisttown/build
RUN cmake ../ -G "Unix Makefiles"  -DCMAKE_TOOLCHAIN_FILE=/usr/lib/x86_64-linux-gnu/cmake/Qt6/qt.toolchain.cmake && make -j4 app

# This command runs your application, comment out this line to compile only
#CMD ["./heisttown"]

LABEL Name=heisttown Version=0.0.1
