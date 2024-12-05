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

# Link OpenCV, Boost libraries and engine library
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} engine)
