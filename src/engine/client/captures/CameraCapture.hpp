#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include "iDevice.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

class CameraCapture : public iDevice {
public:
    int setDevice(const std::string& devicePath) override;
    int enableDevice() override;
    int disableDevice() override;
    cv::Mat getFrame() override;
};

#endif // CAMERACAPTURE_H
