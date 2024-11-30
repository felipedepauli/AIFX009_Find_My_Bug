#include "client/captures/CameraCapture.h"
#include <opencv2/opencv.hpp>

cv::VideoCapture camera;

int CameraCapture::setDevice(const std::string& devicePath) {
    try {
        int cameraID = std::stoi(devicePath); // Converte o caminho para ID da câmera
        std::cout << "[CameraCapture] Setting device with ID: " << cameraID << std::endl;
        camera.open(cameraID);

        if (camera.isOpened()) {
            return 0; // Sucesso
        } else {
            std::cerr << "[CameraCapture] Failed to open camera with ID: " << cameraID << std::endl;
            return -1;
        }
    } catch (const std::exception& e) {
        std::cerr << "[CameraCapture] Invalid camera ID: " << devicePath << " - " << e.what() << std::endl;
        return -1;
    }
}

int CameraCapture::enableDevice() {
    if (camera.isOpened()) {
        std::cout << "[CameraCapture] Camera enabled successfully." << std::endl;
        return 0;
    } else {
        std::cerr << "[CameraCapture] Camera is not opened!" << std::endl;
        return -1;
    }
}

int CameraCapture::disableDevice() {
    if (camera.isOpened()) {
        camera.release();
        std::cout << "[CameraCapture] Camera disabled." << std::endl;
        return 0;
    } else {
        std::cerr << "[CameraCapture] Camera was not active." << std::endl;
        return -1;
    }
}

cv::Mat CameraCapture::getFrame() {
    if (!camera.isOpened()) {
        std::cerr << "[CameraCapture] Camera is not enabled!" << std::endl;
        return cv::Mat(); // Retorna uma matriz vazia
    }

    cv::Mat frame;
    camera >> frame; // Captura o frame da câmera

    if (frame.empty()) {
        std::cerr << "[CameraCapture] Failed to capture a frame!" << std::endl;
        return cv::Mat(); // Retorna uma matriz vazia
    }

    std::cout << "[CameraCapture] Frame captured successfully." << std::endl;
    return frame; // Retorna o frame capturado
}
