# Configurações para Windows 64 bits
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Compilador POSIX para cross-compilation
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc-posix)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++-posix)
set(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)

# Caminho para o OpenCV estático
set(OpenCV_DIR "/home/fpauli/aif/git/AIFX009_Find_My_Bug/3rdbuild/opencv/build_win/")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,--whole-archive -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -Wl,--no-whole-archive")


# Configuração para linkagem estática do MinGW
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32 ${OpenCV_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)