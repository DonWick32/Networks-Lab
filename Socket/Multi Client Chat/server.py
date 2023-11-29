import threading
import socket

host = '127.0.0.1'
port = 9998

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

clients = []
nicknames = []

def broadcast(message, not_client=None):
    message = message.encode('utf-8')
    for client in clients:
        if client != not_client:
            client.send(message)

def handle(client):
    while True:
        try:
            message = client.recv(1024).decode('utf-8')
            print(message)
            broadcast(message, client)
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            nickname = nicknames[index]
            broadcast(f"{nickname} left the chat.")
            nicknames.remove(nickname)
            break

def receive():
    while True:
        client, address = server.accept()
        print("Connected with", address)

        client.send("NICK".encode('utf-8'))
        nickname = client.recv(1024).decode('utf-8')
        nicknames.append(nickname)
        clients.append(client)

        print("Nickname of client is", nickname)
        broadcast(f"{nickname} joined the chat.", client)
        client.send("Connnected to server!".encode('utf-8'))

        thread = threading.Thread(target=handle, args=(client,))
        thread.start()

print("Server is listening on port:", port)
receive()
