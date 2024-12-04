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
        // Captura frames até alcançar o intervalo desejado
        while (frameSkipCounter < frameSkipInterval) {
            videoCapture >> frame;
            if (frame.empty()) {
                std::cout << "[VideoCapture] End of video reached." << std::endl;
                return cv::Mat(); // Retorna uma matriz vazia
            }
            frameSkipCounter++;
        }

        frameSkipCounter = 0; // Reseta o contador após capturar o frame desejado

        // Reduz a resolução para 240x240
        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(400, 300));

        // Converte o frame para escala de cinza
        cv::Mat grayFrame;
        cv::cvtColor(resizedFrame, grayFrame, cv::COLOR_BGR2GRAY);

        std::cout << "[VideoCapture] Frame captured, resized to 240x240, and converted to grayscale." << std::endl;

        return grayFrame; // Retorna o frame processado
    } else {
        std::cerr << "[VideoCapture] Video capture is not enabled." << std::endl;
        return cv::Mat(); // Retorna uma matriz vazia se o vídeo não está habilitado
    }
}
