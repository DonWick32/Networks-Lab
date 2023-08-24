from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

ip = '127.0.0.1'
port = 9999
buffer_size = 4096

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
        msg = input()
        client_socket.send(msg.encode('utf-8'))
        if (msg == 'exit'):
            client_socket.close()
            break

sender = Thread(target = send)
receiver = Thread(target = receive)

sender.start()
receiver.start()