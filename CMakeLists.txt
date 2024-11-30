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

# Configuração para Boost em 3rdparty
set(Boost_NO_SYSTEM_PATHS ON)
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/3rdparty/boost/src/build")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

find_package(Boost REQUIRED COMPONENTS system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${BOOST_LIBRARYDIR})
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${BOOST_LIBRARYDIR}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()


# Diretórios de include
include_directories(${CMAKE_SOURCE_DIR}/include/engine/ ${OpenCV_INCLUDE_DIRS})

# Adiciona subdiretórios de clientes e servidores
add_subdirectory(src/engine/client)
add_subdirectory(src/engine/server)

# Mensagem de status
message(STATUS "Architecture: ${ARCH}")
message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
