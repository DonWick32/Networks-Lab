from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from threading import Thread

ip = '127.0.0.1'
port = 9999
buffer_size = 1024

server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
server_socket.bind((ip, port))
server_socket.listen()
print('Server has started.')

clients = []
client_address = []

def broadcast(msg, client_socket):
    for c in clients:
        if (c != client_socket):
            c.send(msg)

def handle_client(client):
    while True:
        try:
            msg = client.recv(buffer_size)
            ind = clients.index(client)
            address = client_address[ind]

            text = msg.decode('utf-8')

            if text == "exit":
                clients.remove(client)
                del client_address[ind]
                client.close()
                broadcast(f"{address} has disconnected!".encode('utf-8'), client)
                print(address, "has disconnected!")
                break
            else:
                print(f"Received: '{text}' from {address}")
                broadcast(f"{address} : {text} ".encode('utf-8'), client)

        except:
            ind = clients.index(client)
            clients.remove(client)
            address = client_address[ind]
            del client_address[ind]
            client.close()
            broadcast(f"{address} has disconnected!".encode('utf-8'), client)
            print(address, "has disconnected!")
            break


while True:
    client_socket, addr = server_socket.accept()
    print("Connected to:", addr)
    clients.append(client_socket)
    client_address.append(addr)

    client_socket.send('Connected to server.'.encode('utf-8'))

    thread = Thread(target = handle_client, args = (client_socket,))
    thread.start()