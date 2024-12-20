# Configure the server binary
add_executable(
    server
    Server.cpp
    processing/vision/VisionProcessor.cpp
    processing/vision/detectors/implYolo.cpp
    connectors/Kafka.cpp
)
# Find and link librdkafka
find_path(RDKAFKA_INCLUDE_DIR rdkafka.h PATHS /usr/include /usr/include/librdkafka /usr/local/include /usr/local/include/librdkafka)
find_library(RDKAFKA_LIBRARY NAMES rdkafka HINTS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib)

if (RDKAFKA_INCLUDE_DIR AND RDKAFKA_LIBRARY)
    message(STATUS "Found librdkafka: ${RDKAFKA_LIBRARY}")
    include_directories(${RDKAFKA_INCLUDE_DIR})
    target_link_libraries(server PRIVATE ${RDKAFKA_LIBRARY})
else()
    message(FATAL_ERROR "librdkafka not found")
endif()

# Link the OpenCV, Boost, engine, libbytetrack and Kafka libraries
target_link_libraries(server PRIVATE 
    engine 
    ${Boost_LIBRARIES} 
    ${OpenCV_LIBS} 
    ${CMAKE_SOURCE_DIR}/libs/libbytetrack.so 
    ${RDKAFKA_LIBRARIES}   # Kafka libraries
)

# Include Kafka headers
target_include_directories(server PRIVATE 
    ${RDKAFKA_INCLUDE_DIRS}
)
