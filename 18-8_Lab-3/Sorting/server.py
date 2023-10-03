from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

ip = '127.0.0.1'
port = 9999
buffer_size = 1024

server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.bind((ip, port))
server_socket.listen()
print('Server has started.')

def handle_client(client):
    def merge(arr, l, m, r):
        n1, n2  = m - l + 1, r - m

        L, R = [0] * n1, [0] * n2

        for i in range(0, n1):
            L[i] = arr[l + i]

        for j in range(0, n2):
            R[j] = arr[m + 1 + j]

        i, j, k = 0, 0, l

        while i < n1 and j < n2:
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < n1:
            arr[k] = L[i]
            i += 1
            k += 1

        while j < n2:
            arr[k] = R[j]
            j += 1
            k += 1

    def mergeSort(arr, l, r):
        if l < r:
            mid = (l + r) // 2
            mergeSort(arr, l, mid)
            mergeSort(arr, mid + 1, r)
            merge(arr, l, mid, r)

    while True:
        try:
            msg = client.recv(buffer_size)
            text = msg.decode('utf-8')

            n, arr = text.split(":")
            arr = arr.replace("[", "").replace("]", "").replace(",", "")
            n = int(n)
            arr = list(map(int, arr.split(" ")))

            mergeSort(arr, 0, n - 1)

            print("Sorted", n, "number(s).")
            msg = "Sorted List:\n"
            msg += str(arr)

            client_socket.send(msg.encode('utf-8'))

        except:
            client.close()


while True:
    client_socket, addr = server_socket.accept()
    print("Connected to:", addr)

    client_socket.send('Connected to server.'.encode('utf-8'))

    thread = Thread(target = handle_client, args = (client_socket,))
    thread.start()