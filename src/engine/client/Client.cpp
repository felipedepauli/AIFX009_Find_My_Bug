#include "Client.hpp"
#include "../Comm.hpp"

// Declares the function parseInputType
InputType parseInputType(const std::string& typeStr) {
    if (typeStr == "cam") return InputType::cam;
    if (typeStr == "stream") return InputType::streaming;
    if (typeStr == "video") return InputType::video;
    if (typeStr == "dir") return InputType::dir;
    throw std::invalid_argument("Invalid input type: " + typeStr);
}

// Constructor: Instantiates the correct device based on the input type
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

// Configures the device, captures frames and sends them to the server
void Client::run(const std::string& devicePath) {
    if (capture->setDevice(devicePath) != 0) {
        std::cerr << "[Client] Failed to set up the device: " << devicePath << std::endl;
        return;
    }

    if (capture->enableDevice() != 0) {
        std::cerr << "[Client] Failed to enable the device." << std::endl;
        return;
    }

    // Establishes connection with the server
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);
    try {
        boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        boost::asio::connect(socket, endpoints);
        std::cout << "[Client] Connected to server at 127.0.0.1:8080" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Client] Failed to connect to server: " << e.what() << std::endl;
        capture->disableDevice();
        return;
    }

    while (true) {
        cv::Mat frame = capture->getFrame();
        if (frame.empty()) {
            std::cout << "[Client] End of video or no more frames." << std::endl;
            break;
        }

        // Encodes the frame in JPEG
        std::vector<uchar> buffer;
        if (!cv::imencode(".jpg", frame, buffer)) {
            std::cerr << "[Client] Failed to encode frame." << std::endl;
            continue;
        }

        // Sends the frame to the server
        try {
            uint32_t frameSize = htonl(buffer.size());
            boost::asio::write(socket, boost::asio::buffer(&frameSize, sizeof(frameSize))); // Sends size
            boost::asio::write(socket, boost::asio::buffer(buffer));             // Sends data
            std::cout << "[Client] Sent frame of size " << buffer.size() << " bytes" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "[Client] Error sending frame: " << e.what() << std::endl;
            break;
        }

        // // Displays the frame
        // cv::imshow("Video Playback", frame);

        // // Waits 30ms or exits if 'q' is pressed
        // if (cv::waitKey(30) == 'q') {
        //     std::cout << "[Client] Playback interrupted by user." << std::endl;
        //     break;
        // }
    }

    capture->disableDevice();
    // cv::destroyAllWindows();

    // Closes the connection with the server
    try {
        uint32_t frameSize = htonl(1); // Zero indicates termination
        boost::asio::write(socket, boost::asio::buffer(&frameSize, sizeof(frameSize))); // Sends termination signal
        socket.close();
        std::cout << "[Client] Connection closed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Client] Error closing connection: " << e.what() << std::endl;
    }

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
