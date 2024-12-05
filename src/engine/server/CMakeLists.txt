# Configure the server binary
add_executable(
    server
    Server.cpp
    processing/vision/VisionProcessor.cpp
    processing/vision/implYolo.cpp
)

# Link the OpenCV, Boost, engine and libbytetrack libraries
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} engine bytetrack)
