import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ("127.0.0.1", 9999)

client.sendto("Hello Server!".encode('utf-8'), server_address)

print(client.recvfrom(1024)[0].decode('utf-8'))
client.close()