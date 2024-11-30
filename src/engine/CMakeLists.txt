# Cria uma biblioteca para o código compartilhado do engine
add_library(engine SHARED Comm.cpp)

# Inclui diretórios de cabeçalhos para o engine
target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/include/engine)

# Linka dependências necessárias ao engine
target_link_libraries(engine PUBLIC ${Boost_LIBRARIES} ${OpenCV_LIBS})

add_subdirectory(client)
add_subdirectory(server)