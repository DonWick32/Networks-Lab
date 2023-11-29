import socket
import pickle

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('127.0.0.1', 9992))

print(client.recv(1024).decode('utf-8'))
array = [10, 20, 5, 30, -4]

# Use pickle to serialize the array
message = pickle.dumps(array)

client.send(message)

data = client.recv(1024)
sorted_array = pickle.loads(data)
print("Sorted Array:", sorted_array)

client.close()
