#include "VideoCapture.hpp"

int VideoCapture::setDevice(const std::string& devicePath) {
    std::cout << "[VideoCapture] Setting video file path: " << devicePath << std::endl;
    videoCapture.open(devicePath);
    if (!videoCapture.isOpened()) {
        std::cerr << "[VideoCapture] Failed to open video file: " << devicePath << std::endl;
        return -1;
    }
    return 0;
}

int VideoCapture::enableDevice() {
    std::cout << "[VideoCapture] Enabling video capture." << std::endl;
    return 0;
}

int VideoCapture::disableDevice() {
    std::cout << "[VideoCapture] Disabling video capture." << std::endl;
    videoCapture.release();
    return 0;
}

cv::Mat VideoCapture::getFrame() {
    cv::Mat frame;

    if (videoCapture.isOpened()) {
        while (frameSkipCounter < frameSkipInterval) {
            videoCapture >> frame;
            if (frame.empty()) {
                std::cout << "[VideoCapture] End of video reached." << std::endl;
                return cv::Mat();
            }
            frameSkipCounter++;
        }

        frameSkipCounter = 0;

        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(640, 640));

        return resizedFrame;
    } else {
        std::cerr << "[VideoCapture] Video capture is not enabled." << std::endl;
        return cv::Mat();
    }
}