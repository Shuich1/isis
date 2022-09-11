import time
from random import randint
from kafka import KafkaProducer

producer = KafkaProducer(bootstrap_servers='localhost:9092')
while(True):
    value = str(randint(0, 100))
    producer.send('random', value.encode('utf-8'))
    time.sleep(2.0)