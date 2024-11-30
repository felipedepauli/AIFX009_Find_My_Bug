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

# Inclui o toolchain
if(CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

# Configura o OpenCV
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Diretórios de include
include_directories(${CMAKE_SOURCE_DIR}/include/engine/ ${OpenCV_INCLUDE_DIRS})

# Adiciona subdiretórios de clientes e servidores
add_subdirectory(src/engine/)

# Mensagem de status
message(STATUS "Architecture: ${ARCH}")
message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
