#include "client/captures/VideoCapture.h"

int VideoCapture::setDevice(const std::string& devicePath) {
    std::cout << "[VideoCapture] Setting video file path: " << devicePath << std::endl;
    videoCapture.open(devicePath); // Usando cv::VideoCapture para abrir o vídeo
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
    videoCapture.release(); // Libera o recurso do vídeo
    return 0;
}

cv::Mat VideoCapture::getFrame() {
    cv::Mat frame;
    if (videoCapture.isOpened()) {
        videoCapture >> frame; // Captura o próximo frame
        if (frame.empty()) {
            std::cout << "[VideoCapture] End of video reached." << std::endl;
        }
    } else {
        std::cerr << "[VideoCapture] Video capture is not enabled." << std::endl;
    }
    return frame; // Retorna o frame capturado (ou vazio se acabou)
}
