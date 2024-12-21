#include "Kafka.hpp"
#include <iostream>
#include <vector>

// Constructor
Kafka::Kafka(const std::string& broker, const std::string& topic)
    : broker(broker), topic(topic), kafkaProducer(nullptr), kafkaConf(nullptr), kafkaTopic(nullptr) {
    if (!initializeProducer()) {
        std::cerr << "[Kafka            ] Failed to initialize Kafka producer." << std::endl;
    } else {
        std::cout << "[Kafka            ] Successfully initialized Kafka producer for broker: " << broker << ", topic: " << topic << std::endl;
    }
}

// Destructor
Kafka::~Kafka() {
    if (kafkaTopic) {
        rd_kafka_topic_destroy(kafkaTopic);
    }

    if (kafkaProducer) {
        // Flush to ensure all messages are sent before destroying
        rd_kafka_flush(kafkaProducer, 5000); // Wait up to 5000ms
        rd_kafka_destroy(kafkaProducer);
    }
}

// Private method to initialize the Kafka producer
bool Kafka::initializeProducer() {
    kafkaConf = rd_kafka_conf_new();

    if (rd_kafka_conf_set(kafkaConf, "bootstrap.servers", broker.c_str(), errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        std::cerr << "[Kafka            ] Failed to set Kafka configuration: " << errstr << std::endl;
        return false;
    }

    if (rd_kafka_conf_set(kafkaConf, "log.connection.close", "false", errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
    std::cerr << "[Kafka            ] Failed to set Kafka configuration: " << errstr << std::endl;
    return false;
}

    kafkaProducer = rd_kafka_new(RD_KAFKA_PRODUCER, kafkaConf, errstr, sizeof(errstr));
    if (!kafkaProducer) {
        std::cerr << "[Kafka            ] Failed to create Kafka producer: " << errstr << std::endl;
        return false;
    }

    kafkaTopic = rd_kafka_topic_new(kafkaProducer, topic.c_str(), nullptr);
    if (!kafkaTopic) {
        std::cerr << "[Kafka            ] Failed to create Kafka topic: " << rd_kafka_err2str(rd_kafka_last_error()) << std::endl;
        return false;
    }

    return true;
}

// Method to send a message containing the frame and JSON data to the Kafka topic
int Kafka::produce(const cv::Mat& frame, const nlohmann::json& jsonData) {
    try {
        // Convert frame to a byte buffer (encoded as JPEG)
        std::vector<uchar> buffer;
        if (!cv::imencode(".jpg", frame, buffer)) {
            std::cerr << "[Kafka            ] Failed to encode frame as JPEG." << std::endl;
            return 1;
        }

        // Combine JSON and image data
        std::string jsonString = jsonData.dump();
        std::string delimiter = "---FRAME_SEPARATOR---";
        std::string messagePayload = jsonString + delimiter + std::string(buffer.begin(), buffer.end());

        std::cout << "[Kafka            ] Sending message to topic: " << topic << std::endl;
        std::cout << "[Kafka            ] Message size: " << messagePayload.size() << " bytes" << std::endl;
        std::cout << "[Kafka            ] Message: " << messagePayload.substr(0, 100) << "..." << std::endl;

        // Send the message to Kafka
        int err = rd_kafka_produce(
            kafkaTopic,
            RD_KAFKA_PARTITION_UA, // Use the available partition
            RD_KAFKA_MSG_F_COPY,   // Copy the payload
            (void*)messagePayload.c_str(),
            messagePayload.size(),
            nullptr, // Key
            0,       // Key length
            nullptr  // Opaque
        );

        if (err != 0) {
            std::cerr << "[Kafka            ] Failed to send message: " << rd_kafka_err2str(rd_kafka_last_error()) << std::endl;
            return 1;
        }

        std::cout << "[Kafka            ] Message sent successfully to topic: " << topic << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "[Kafka            ] Exception while sending message: " << e.what() << std::endl;
        return 1;
    }
}
