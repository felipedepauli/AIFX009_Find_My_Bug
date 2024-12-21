#ifndef CLIENT_H
#define CLIENT_H

#include "Capture.hpp"
#include "captures/CameraCapture.hpp"
#include "captures/StreamingCapture.hpp"
#include "captures/VideoCapture.hpp"
#include "captures/DirectoryCapture.hpp"
#include <memory>
#include <string>
#include <iostream>

// Define os tipos de entrada
enum class InputType {
    cam,
    streaming,
    video,
    dir
};

class Client {
private:
    std::unique_ptr<Capture> capture;

public:
    explicit Client(InputType type);
    void run(const std::string& devicePath);
};

// Declara a função parseInputType
InputType parseInputType(const std::string& typeStr);

#endif // CLIENT_H
