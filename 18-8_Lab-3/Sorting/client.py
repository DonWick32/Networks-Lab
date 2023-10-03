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
        n = int(input())
        if n <= 0:
            client_socket.close()
            break

        arr = list(map(int,input("\nEnter the numbers: ").strip().split()))[:n]

        msg = str(n) + ":" + str(arr)

        client_socket.send(msg.encode('utf-8'))

sender = Thread(target = send)
receiver = Thread(target = receive)

receiver.start()
sender.start()