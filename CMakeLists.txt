cmake_minimum_required(VERSION 3.16)
project(AIFX009_Find_My_Bug)

# Configurações gerais
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Diretórios de include
include_directories(${CMAKE_SOURCE_DIR}/src)

# Coleta todos os arquivos do diretório src
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Executável principal
add_executable(aifx009_main ${SOURCES})

# Adiciona bibliotecas externas
find_package(OpenCV REQUIRED)
target_link_libraries(aifx009_main PRIVATE ${OpenCV_LIBS})

# Configuração para testes
enable_testing()
add_subdirectory(tests)

# Mensagem de status
message(STATUS "Projeto configurado para OpenCV: ${OpenCV_VERSION}")
