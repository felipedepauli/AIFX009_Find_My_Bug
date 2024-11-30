#ifndef CAPTURE_H
#define CAPTURE_H

#include "client/captures/iDevice.h"
#include <memory>

class Capture {
private:
    std::unique_ptr<iDevice> device;

public:
    explicit Capture(std::unique_ptr<iDevice> device) : device(std::move(device)) {}

    // Configura o dispositivo (chama o método do iDevice encapsulado)
    int setDevice(const std::string& devicePath) {
        return device->setDevice(devicePath);
    }

    // Ativa o dispositivo
    int enableDevice() {
        return device->enableDevice();
    }

    // Desativa o dispositivo
    int disableDevice() {
        return device->disableDevice();
    }

    // Obtém um frame capturado
    cv::Mat getFrame() {
        return device->getFrame();
    }
};

#endif // CAPTURE_H
