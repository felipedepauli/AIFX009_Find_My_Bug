#ifndef STREAMINGCAPTURE_H
#define STREAMINGCAPTURE_H

#include "iDevice.h"
#include <iostream>
#include <opencv2/opencv.hpp>

class StreamingCapture : public iDevice {
public:
    int setDevice(const std::string& devicePath) override;
    int enableDevice() override;
    int disableDevice() override;
    cv::Mat getFrame() override;
};

#endif // STREAMINGCAPTURE_H
