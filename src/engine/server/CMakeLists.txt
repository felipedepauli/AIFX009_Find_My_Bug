# Configuração do binário do servidor
add_executable(
    server
    Server.cpp
    processing/vision/VisionProcessor.cpp
    processing/vision/implYolo.cpp
)

# Linka bibliotecas do OpenCV, Boost e a biblioteca engine
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} engine)
