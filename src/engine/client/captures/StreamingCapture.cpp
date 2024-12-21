#include "StreamingCapture.hpp"

int StreamingCapture::setDevice(const std::string& devicePath) {
    std::cout << "[StreamingCapture] Setting stream URL: " << devicePath << std::endl;
    return 0;
}

int StreamingCapture::enableDevice() {
    std::cout << "[StreamingCapture] Enabling stream capture." << std::endl;
    return 0;
}

int StreamingCapture::disableDevice() {
    std::cout << "[StreamingCapture] Disabling stream capture." << std::endl;
    return 0;
}

cv::Mat StreamingCapture::getFrame() {
    std::cout << "[StreamingCapture] Capturing frame from stream." << std::endl;
    return cv::Mat::zeros(100, 100, CV_8UC3); // Gera uma imagem preta 100x100
}
