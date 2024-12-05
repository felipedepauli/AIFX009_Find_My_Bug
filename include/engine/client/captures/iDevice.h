#ifndef IDEVICE_H
#define IDEVICE_H

#include <opencv2/opencv.hpp>
#include <string>

class iDevice {
public:
    virtual ~iDevice() = default;

    // Configures the device (e.g., video path, streaming URL, or camera ID)
    virtual int setDevice(const std::string& devicePath) = 0;

    // Enables the device for capture
    virtual int enableDevice() = 0;

    // Disables the device
    virtual int disableDevice() = 0;

    // Retrieves a captured frame
    virtual cv::Mat getFrame() = 0;
};

#endif // IDEVICE_H
