# Get the Qt6 Google Test Ubuntu image from Docker Hub
FROM tadekbiela/cpp_development:cpp_development_linux

# Clone heisttown repository
WORKDIR /usr/src
RUN git clone https://github.com/TadekBiela/heisttown.git

ENV XDG_RUNTIME_DIR="/tmp/runtime-root"
ENV LSAN_OPTIONS="suppressions=/usr/src/heisttown/sanitizer_suppressions.supp"

# Set to working directory and build heisttown
WORKDIR /usr/src/heisttown/build
RUN cmake ../
RUN cmake --build . --target all

LABEL Name=heisttown
