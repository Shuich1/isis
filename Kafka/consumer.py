from kafka import KafkaConsumer

consumer = KafkaConsumer('random', bootstrap_servers='localhost:9092')
for message in consumer:
    print("Recieved message: " + message.value.decode('utf-8') + " on topic: " + message.topic)