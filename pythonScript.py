import requests
import random
import time

for i in range(1, 100):
    data = "{'data':" + str(random.randint(10, 500)) + "}"
    x = requests.post("http://localhost/liveSensorData", {"data": data})
    print(data)
    time.sleep(5)

