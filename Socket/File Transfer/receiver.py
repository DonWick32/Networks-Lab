import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('127.0.0.1', 9997))
server.listen()

client, address = server.accept()

fileName = client.recv(1024).decode()

file = open(fileName, "wb")

fileBytes = b""

done = False

while not done:
    data = client.recv(1024)
    if data[-6:] == b"<TATA>":
        done = True
        fileBytes += data[:-6]  # Remove the "<TATA>" marker from the last chunk
    else:
        fileBytes += data

file.write(fileBytes)

file.close()
client.close()
server.close()
