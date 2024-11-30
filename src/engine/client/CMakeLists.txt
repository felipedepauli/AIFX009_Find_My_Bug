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

# Linka bibliotecas do OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS})
