# Use a lightweight Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set the maintainer
LABEL maintainer="Felipe C. de Pauli <fcdpauli@gmail.com>"

# Set environment variables to prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install essential build dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    g++ \
    git \
    wget \
    curl \
    libssl-dev \
    pkg-config \
    ca-certificates \
    libeigen3-dev \
    libboost-system-dev \
    ffmpeg \
    librdkafka-dev \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    nlohmann-json3-dev \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /workspace

# 4. Clone the OpenCV repositories
RUN git clone -b 4.10.0 https://github.com/opencv/opencv.git && \
    git clone -b 4.10.0 https://github.com/opencv/opencv_contrib.git

# 5. Compile the OpenCV
RUN cd opencv && \
    mkdir -p build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -D OPENCV_EXTRA_MODULES_PATH=/workspace/opencv_contrib/modules \
          -D WITH_FFMPEG=ON \
          -D WITH_GSTREAMER=ON \
          -D WITH_OPENCL=ON \
          -D BUILD_TESTS=OFF \
          -D BUILD_PERF_TESTS=OFF \
          -D BUILD_EXAMPLES=OFF \
          -D BUILD_opencv_python3=OFF \
          -D OPENCV_ENABLE_NONFREE=ON \
          .. && \
    make -j$(nproc) && \
    make install

# 6. Clean up temporary files (to reduce the image size)
RUN rm -rf /workspace/opencv /workspace/opencv_contrib

# 7. Check the installation
CMD python3 -c "import cv2; print('OpenCV version:', cv2.__version__)"

# 8. Set the default entrypoint to keep the container running
CMD ["/bin/bash"]
