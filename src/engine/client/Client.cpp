#include "client/Client.h"

// Declara a função parseInputType
InputType parseInputType(const std::string& typeStr) {
    if (typeStr == "cam") return InputType::cam;
    if (typeStr == "stream") return InputType::streaming;
    if (typeStr == "video") return InputType::video;
    if (typeStr == "dir") return InputType::dir;
    throw std::invalid_argument("Invalid input type: " + typeStr);
}

// Construtor: Instancia o dispositivo correto com base no tipo de entrada
Client::Client(InputType type) {
    switch (type) {
        case InputType::cam:
            capture = std::make_unique<Capture>(std::make_unique<CameraCapture>());
            break;
        case InputType::streaming:
            capture = std::make_unique<Capture>(std::make_unique<StreamingCapture>());
            break;
        case InputType::video:
            capture = std::make_unique<Capture>(std::make_unique<VideoCapture>());
            break;
        case InputType::dir:
            capture = std::make_unique<Capture>(std::make_unique<DirectoryCapture>());
            break;
        default:
            throw std::invalid_argument("Invalid input type.");
    }
}

void Client::run(const std::string& devicePath) {
    if (capture->setDevice(devicePath) != 0) {
        std::cerr << "[Client] Failed to set up the device: " << devicePath << std::endl;
        return;
    }

    if (capture->enableDevice() != 0) {
        std::cerr << "[Client] Failed to enable the device." << std::endl;
        return;
    }

    std::cout << "[Client] Starting video playback..." << std::endl;

    // Loop para capturar e exibir frames
    while (true) {
        cv::Mat frame = capture->getFrame();
        if (frame.empty()) break; // Sai do loop se o vídeo terminar

        // Mostra o frame na tela
        cv::imshow("Video Playback", frame);

        // Aguarda por 30ms ou até que uma tecla seja pressionada
        if (cv::waitKey(30) >= 0) break;
    }

    capture->disableDevice();
    cv::destroyAllWindows(); // Fecha a janela de exibição
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_type> <device_path>" << std::endl;
        std::cerr << "Input types: cam, stream, video, dir" << std::endl;
        return 1;
    }

    try {
        InputType inputType = parseInputType(argv[1]);
        std::cout << "[Client] Input type: " << argv[1] << std::endl;
        std::string devicePath = argv[2];

        Client client(inputType);
        client.run(devicePath);

    } catch (const std::exception& e) {
        std::cerr << "[Client] Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
