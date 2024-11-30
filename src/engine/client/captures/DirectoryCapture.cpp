#include "client/captures/DirectoryCapture.h"

int DirectoryCapture::setDevice(const std::string& devicePath) {
    std::cout << "[DirectoryCapture] Setting directory path: " << devicePath << std::endl;
    return 0;
}

int DirectoryCapture::enableDevice() {
    std::cout << "[DirectoryCapture] Enabling directory capture." << std::endl;
    return 0;
}

int DirectoryCapture::disableDevice() {
    std::cout << "[DirectoryCapture] Disabling directory capture." << std::endl;
    return 0;
}

cv::Mat DirectoryCapture::getFrame() {
    std::cout << "[DirectoryCapture] Capturing frame from directory." << std::endl;
    return cv::Mat::zeros(100, 100, CV_8UC3); // Gera uma imagem preta 100x100
}
