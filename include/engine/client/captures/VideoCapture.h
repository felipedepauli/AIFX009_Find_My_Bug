#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include "iDevice.h"
#include <iostream>
#include <opencv2/opencv.hpp>

class VideoCapture : public iDevice {
private:
    cv::VideoCapture videoCapture; // Declaração do objeto para manipular vídeos
public:
    int setDevice(const std::string& devicePath) override;
    int enableDevice() override;
    int disableDevice() override;
    cv::Mat getFrame() override;
};

#endif // VIDEOCAPTURE_H
