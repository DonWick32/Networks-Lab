from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

IP_ADDRESS = "127.0.0.1"
PORT = "9696"
BUFFER_SIZE = 1024

server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.bind((IP_ADDRESS, PORT))
server_socket.listen()
print("Server has started.")

questions = {
    0 : ["Which lang is used for App Development?", ("Kotlin", "Go-lang", "C++", "Python"), 0]
}

clients = {}

def handle_client(client):
    pass

while True:
    client_socket, client_address = server_socket.accept()
    client_id = len(clients)
    print("Connected to Client:", client_id + 1)
    clients[client_id] = {client_address, client_socket}
    
    msg = "Connected to Server."
    
    client_socket.send(msg.encode('utf-8'))
    thread = Thread(target = handle_client, args = (clients[client_id],))
    
    
    




