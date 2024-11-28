file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

add_executable(aifx009_tests ${TEST_SOURCES})
target_link_libraries(aifx009_tests PRIVATE ${OpenCV_LIBS})

# Adiciona os testes
add_test(NAME CaptureTests COMMAND aifx009_tests)
add_test(NAME CommunicationTests COMMAND aifx009_tests)
