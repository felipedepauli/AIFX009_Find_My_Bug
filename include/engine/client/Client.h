#ifndef CLIENT_H
#define CLIENT_H

#include "Capture.h"
#include "captures/CameraCapture.h"
#include "captures/StreamingCapture.h"
#include "captures/VideoCapture.h"
#include "captures/DirectoryCapture.h"
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
