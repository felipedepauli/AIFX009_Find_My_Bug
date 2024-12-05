cmake_minimum_required(VERSION 3.16)
project(AIFX009_Find_My_Bug)

# Configurações gerais
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ativar build tipo Debug por padrão
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define opções de arquitetura (ARCH)
set(ARCH "PC_LINUX_64" CACHE STRING "Target architecture")
set_property(CACHE ARCH PROPERTY STRINGS PC_LINUX_64 PC_WIN_64)

# Configura o toolchain com base na ARCH selecionada
if(ARCH STREQUAL "PC_LINUX_64")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchains/pc_linux_64.cmake")
elseif(ARCH STREQUAL "PC_WIN_64")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchains/pc_win_64.cmake")
else()
    message(FATAL_ERROR "Unsupported architecture: ${ARCH}")
endif()

# Include toolchain file
if(CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

# Configure OpenCV
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include/engine/ ${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include/3rdparty/ ${OpenCV_INCLUDE_DIRS})
include_directories(/usr/local/include/eigen3 ${OpenCV_INCLUDE_DIRS})

# Add subdirectories for clients and servers
add_subdirectory(src/engine/)

# Status message
message(STATUS "Architecture: ${ARCH}")
message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
