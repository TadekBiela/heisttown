# Get the Qt6 Google Test Ubuntu image from Docker Hub
FROM tadekbiela/cpp_development:qt6_gtest_cpp_image

# Clone heisttown repository
WORKDIR /usr/src
RUN git clone https://github.com/TadekBiela/heisttown.git

# Set to working directory and build heisttown
WORKDIR /usr/src/heisttown/build
RUN cmake ../ && make -j4 app

LABEL Name=heisttown
