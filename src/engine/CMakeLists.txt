# Create a library for the shared engine code
add_library(engine STATIC Comm.cpp)

# Include header directories for the engine
target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/src/include/engine)

# Link necessary dependencies to the engine
target_link_libraries(engine PUBLIC ${Boost_LIBRARIES} ${OpenCV_LIBS})

add_subdirectory(client)
add_subdirectory(server)