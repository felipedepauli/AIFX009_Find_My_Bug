#ifndef KAFKA_H
#define KAFKA_H

#include <string>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <librdkafka/rdkafka.h>

class Kafka {
private:
    std::string broker;
    std::string topic;
    rd_kafka_t* kafkaProducer;
    rd_kafka_conf_t* kafkaConf;
    rd_kafka_topic_t* kafkaTopic;
    char errstr[512]; // Buffer for error messages

    // Private method to initialize the Kafka producer
    bool initializeProducer();

public:
    // Constructor
    Kafka(const std::string& broker, const std::string& topic);

    // Destructor
    ~Kafka();

    // Method to send a message containing the frame and JSON data to the Kafka topic
    int produce(const cv::Mat& frame, const nlohmann::json& jsonData);
};

#endif // KAFKA_H
