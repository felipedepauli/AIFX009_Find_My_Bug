from confluent_kafka import Consumer, KafkaError

def consume_kafka_messages(broker, topic):
    # Kafka consumer configuration
    consumer_config = {
        'bootstrap.servers': broker,
        'group.id': 'python-consumer-group',
        'auto.offset.reset': 'earliest'  # Start from the beginning of the topic
    }
    consumer = Consumer(consumer_config)
    consumer.subscribe([topic])

    try:
        print(f"Listening to topic '{topic}'...")
        while True:
            msg = consumer.poll(1.0)  # Poll for messages (timeout=1s)
            if msg is None:
                continue
            if msg.error():
                if msg.error().code() == KafkaError._PARTITION_EOF:
                    continue  # End of partition reached
                else:
                    print(f"Error: {msg.error()}")
                    continue

            # Process the received message
            payload = msg.value()
            if payload is None:
                continue
            
            try:
                # Decode the payload using the delimiter
                parts = payload.split(b"---FRAME_SEPARATOR---", 1)
                if len(parts) != 2:
                    print("[Consumer] Malformed message: missing separator.")
                    continue
                
                json_data = parts[0].decode('utf-8')  # Decode the JSON part
                image_data = parts[1]  # Binary image data

                print(f"[Consumer] JSON Data: {json_data}")
                print(f"[Consumer] Image size: {len(image_data)} bytes")

                # Optional: Save the image to verify
                with open("received_image.jpg", "wb") as f:
                    f.write(image_data)
                    print("[Consumer] Image saved as 'received_image.jpg'")

            except Exception as e:
                print(f"[Consumer] Error processing message: {e}")

    except KeyboardInterrupt:
        print("Exiting consumer...")
    finally:
        consumer.close()

# Configure broker and topic
BROKER = "localhost:9092"
TOPIC = "detections"

consume_kafka_messages(BROKER, TOPIC)
