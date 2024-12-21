#ifndef DIRECTORYCAPTURE_H
#define DIRECTORYCAPTURE_H

#include "iDevice.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

class DirectoryCapture : public iDevice {
public:
    int setDevice(const std::string& devicePath) override;
    int enableDevice() override;
    int disableDevice() override;
    cv::Mat getFrame() override;
};

#endif // DIRECTORYCAPTURE_H
