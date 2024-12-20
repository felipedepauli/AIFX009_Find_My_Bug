# Author    : Felipe Camargo de Pauli
# Contact   : fcdpauli@gmail.com
# Date      : 2021-09-20

# This CMake script sets up the build environment for AIFX009, Find my BUG, an amazing C++ project.

# Minimum version of CMake required
cmake_minimum_required(VERSION 3.16)

# Project name
project(AIFX009_Find_My_Bug)

# Set C++ standard (this is important because we are using C++17 features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activate Debug build type by default (you can change it to Release after testing)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set the target architecture (PC_LINUX_64, PC_WIN_64 or ARM for Raspberry Pi)
set(ARCH "PC_LINUX_64" CACHE STRING "Target architecture")
set_property(CACHE ARCH PROPERTY STRINGS PC_LINUX_64 PC_WIN_64)

# Configure the toolchain based on the selected ARCH
if(ARCH STREQUAL "PC_LINUX_64")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/src/toolchains/pc_linux_64.cmake")
elseif(ARCH STREQUAL "PC_WIN_64")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/src/toolchains/pc_win_64.cmake")
elseif(ARCH STREQUAL "ARM")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/src/toolchains/arm.cmake")
else()
    message(FATAL_ERROR "Unsupported architecture: ${ARCH}")
endif()

# After selecting the toolchain, include it
if(CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

# Look for OpenCV and Boost libraries and set environment variables (like OpenCV_INCLUDE_DIRS)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Directory for header files (the famous include directory - to include, you have to respect the path set here)
include_directories(${CMAKE_SOURCE_DIR}/src/include/engine/ ${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src/include/3rdparty ${OpenCV_INCLUDE_DIRS})
include_directories(/usr/include/eigen3 ${OpenCV_INCLUDE_DIRS})

# Add subdirectories for clients and servers (yes, there are two different applications in this project)
add_subdirectory(src/engine/)

# Status message
message(STATUS "------------------------------------------------------------------------------------")
message(STATUS "Project name        : ${PROJECT_NAME}")
message(STATUS "Architecture        : ${ARCH}")
message(STATUS "Toolchain file      : ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build type          : ${CMAKE_BUILD_TYPE}")
message(STATUS "OpenCV include dirs : ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries    : ${OpenCV_LIBS}")
message(STATUS "------------------------------------------------------------------------------------")
