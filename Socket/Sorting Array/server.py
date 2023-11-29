import socket
import pickle

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('127.0.0.1', 9992))
server.listen()

while True:
    client, address = server.accept()
    print("Connected to", address)
    client.send("Connected to server".encode('utf-8'))

    data = client.recv(1024)
    array = pickle.loads(data)
    
    print("Received Array:", array)
    
    array.sort()

    message = pickle.dumps(array)
    client.send(message)

    client.close()
    break

server.close()
