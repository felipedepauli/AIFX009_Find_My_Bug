#ifndef IDEVICE_H
#define IDEVICE_H

#include <opencv2/opencv.hpp>
#include <string>

class iDevice {
public:
    virtual ~iDevice() = default;

    // Configura o dispositivo (ex.: caminho do vídeo, URL de streaming ou ID da câmera)
    virtual int setDevice(const std::string& devicePath) = 0;

    // Ativa o dispositivo para captura
    virtual int enableDevice() = 0;

    // Desativa o dispositivo
    virtual int disableDevice() = 0;

    // Obtém um frame capturado
    virtual cv::Mat getFrame() = 0;
};

#endif // IDEVICE_H
