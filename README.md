# AIFX009_Find_My_Bug





Opencv
sudo apt update
sudo apt-get install -y build-essential cmake git libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev \
    libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev gfortran \
    libdc1394-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
git clone opencv
git clone opencv_contrib
cd opencv
git checkout 4.10.0
cd ../opencv_contrib
git checkout 4.10.0
cd ../opencv
mkdir build
cd build
cmake   -DWITH_CUDA=ON \
        -DOPENCV_DNN_CUDA=ON \
        -DBUILD_OPENCV_DNN=ON \
        -DOPENCV_DNN_OPENCV=ON \
        -DENABLE_FAST_MATH=ON \
        -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
        -DCUDA_FAST_MATH=ON \
        -DCUDA_ARCH_BIN=8.6 -DCMAKE_CONFIGURATION_TYPES=Release ..
make -j4
make install




