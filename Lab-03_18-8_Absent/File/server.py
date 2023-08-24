from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

ip = '127.0.0.1'
port = 9999
buffer_size = 1024

s_sock = socket(AF_INET, SOCK_STREAM)
s_sock.bind((ip, port))
s_sock.listen()
print('Server has started.')

def handle_client(client):
    while True:
        try:
            msg = client.recv(buffer_size)
            text = msg.decode('utf-8')

            with open('newfile.txt', 'w') as f:
                f.write(text)
            
            with open('newfile.txt', 'r') as f:
                s = f.readlines()
                lc = len(s)
                wc = 0
                cc = 0

                for line in s:
                    words = line.split()
                    wc += len(words)
                    cc += len(line)

            msg = "File uploaded successfully.\n"
            msg += "Line count: " + str(lc) + "\n"
            msg += "Word count: " + str(wc) + "\n"
            msg += "Character count: " + str(cc) + "\n"

            print("File created successfully.")

            c_sock.send(msg.encode('utf-8'))

        except:
            client.close()


while True:
    c_sock, addr = s_sock.accept()
    print("Connected to:", addr)

    c_sock.send('Connected to server.'.encode('utf-8'))

    thread = Thread(target = handle_client, args = (c_sock,))
    thread.start()
