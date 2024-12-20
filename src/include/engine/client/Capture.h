#ifndef CAPTURE_H
#define CAPTURE_H

#include "client/captures/iDevice.h"
#include <memory>

class Capture {
private:
    std::unique_ptr<iDevice> device;

public:
    explicit Capture(std::unique_ptr<iDevice> device) : device(std::move(device)) {}

    // Configures the device (calls the method of the encapsulated iDevice)
    int setDevice(const std::string& devicePath) {
        return device->setDevice(devicePath);
    }

    // Enables the device
    int enableDevice() {
        return device->enableDevice();
    }

    // Disables the device
    int disableDevice() {
        return device->disableDevice();
    }

    // Gets a captured frame
    cv::Mat getFrame() {
        return device->getFrame();
    }
};

#endif // CAPTURE_H
