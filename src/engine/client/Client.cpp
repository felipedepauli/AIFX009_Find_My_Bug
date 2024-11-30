#include "client/Client.h"
#include "Comm.h"

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

// Configura o dispositivo e captura frames
void Client::run(const std::string& devicePath) {
    if (capture->setDevice(devicePath) != 0) {
        std::cerr << "[Client] Failed to set up the device: " << devicePath << std::endl;
        return;
    }

    if (capture->enableDevice() != 0) {
        std::cerr << "[Client] Failed to enable the device." << std::endl;
        return;
    }

    while (true) {
        cv::Mat frame = capture->getFrame();
        if (frame.empty()) {
            std::cout << "[Client] End of video or no more frames." << std::endl;
            break;
        }

        // Exibe o frame
        cv::imshow("Video Playback", frame);

        // Aguarda 30ms ou sai se 'q' for pressionado
        if (cv::waitKey(30) == 'q') {
            std::cout << "[Client] Playback interrupted by user." << std::endl;
            break;
        }
    }

    capture->disableDevice();
    cv::destroyAllWindows();

    // Envia mensagem ao servidor
    Comm comm;
    comm.sendMessage("Processing completed", "127.0.0.1", 8080);
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
