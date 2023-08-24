from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

ip = '127.0.0.1'
port = 9999
buffer_size = 1024

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((ip, port))

def receive():
    while True:
        try:
            msg = client_socket.recv(buffer_size).decode('utf-8')
            print(msg)
        except:
            print('Disconnected from server!')
            client_socket.close()
            break


def send():
    while True:
        file = input("Enter file name: ")
        if file == 'exit':
            client_socket.close()
            break
        
        with open(file, 'r') as f:
            msg = f.read()
            client_socket.send(msg.encode('utf-8'))

sender = Thread(target = send)
receiver = Thread(target = receive)

receiver.start()
sender.start()