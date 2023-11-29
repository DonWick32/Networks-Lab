import socket
import os

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 9997))

file = open("image.png", "rb")
fileSize = os.path.getsize("image.png")

client.send("received_image.png".encode())

data = file.read()
client.sendall(data)
client.send(b"<TATA>")

file.close()
client.close()
