# Define o binário do cliente
add_executable(
    client
    Client.cpp
    Capture.cpp
    captures/CameraCapture.cpp
    captures/StreamingCapture.cpp
    captures/VideoCapture.cpp
    captures/DirectoryCapture.cpp
)

# Linka bibliotecas do OpenCV, Boost e a biblioteca engine
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} engine)
