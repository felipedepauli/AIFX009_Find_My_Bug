# Configuração do binário do servidor
add_executable(server Server.cpp ../Comm.cpp)

# Linka bibliotecas (adicionar conforme necessário)
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/include/engine)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS})
