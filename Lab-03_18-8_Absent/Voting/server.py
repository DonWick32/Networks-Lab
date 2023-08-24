from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from threading import Thread

ip, port, buffer_size = '127.0.0.1', 9999, 4096

s_sock = socket(AF_INET, SOCK_STREAM)
s_sock.bind((ip, port))
s_sock.listen()
print('Server has started.')

candi = ["A", "B", "C", "D", "E"]
votes = [0, 0, 0, 0, 0]

c = []
c_addr = []

def display_votes():
    msg = "Current Votes:\n"

    for i in range(len(candi)):
        msg += f"{i+1}) {candi[i]} - {votes[i]} votes\n"

    msg += (f"Candidate - {candi[votes.index(max(votes))]} is leading!\n")

    print(msg)

def handle_client(client):
    while True:
        try:
            msg = client.recv(buffer_size)
            ind = c.index(client)
            addr = c_addr[ind]

            text = msg.decode('utf-8')

            if text == "exit":
                c.remove(client)
                del c_addr[ind]
                client.close()
                print(addr, "has disconnected!")
                break
            else:
                c_id = int(text)
                if c_id in range(1, len(candi)+1):
                    print(f"{addr} has casted a vote for {candi[c_id-1]}!")
                    votes[c_id - 1] += 1
                    display_votes()
                    client.send("Vote casted!".encode('utf-8'))
                else:
                    client.send("Invalid candidate!".encode('utf-8'))
                

        except:
            ind = c.index(client)
            c.remove(client)
            addr = c_addr[ind]
            del c_addr[ind]
            client.close()
            print(addr, "has disconnected!")
            break


while True:
    c_sock, addr = s_sock.accept()
    print("Connected to:", addr)
    c.append(c_sock)
    c_addr.append(addr)

    msg = "Connected to server.\n"
    msg += "Candidates:\n"
    for i in range(len(candi)):
        msg += f"{i+1}) {candi[i]}\n"
    msg += "Enter the candidate number to vote: "

    c_sock.send(msg.encode('utf-8'))

    thread = Thread(target = handle_client, args = (c_sock,))
    thread.start()