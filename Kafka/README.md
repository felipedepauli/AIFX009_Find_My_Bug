


 ```bash
$ kafka-topics --bootstrap-server localhost:9092 --create --topic detections --partitions 1 --replication-factor 1
 >> Created topic detections.
$ kafka-topics --bootstrap-server localhost:9092 --list
 >> __consumer_offsets
 >> detections
 ```

