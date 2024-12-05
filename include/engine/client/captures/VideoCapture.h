#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include "iDevice.h"
#include <iostream>
#include <opencv2/opencv.hpp>

class VideoCapture : public iDevice {
private:
    int frameSkipCounter = 0;
    int frameSkipInterval = 1;
    cv::VideoCapture videoCapture;
    
public:
    int setDevice(const std::string& devicePath) override;
    int enableDevice() override;
    int disableDevice() override;
    cv::Mat getFrame() override;
};

#endif // VIDEOCAPTURE_H
