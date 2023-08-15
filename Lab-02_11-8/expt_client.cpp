#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8099
#define BUFFER_SIZE 1024

using namespace std;

int client_socket;
char message[BUFFER_SIZE];
char buffer[BUFFER_SIZE];
pthread_t send_thread, receive_thread;

void* send_function(void* arg) {
    while (1) {
        cout << "Enter message (or 'exit' to quit):" << endl;
        fgets(message, BUFFER_SIZE, stdin);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        if (send(client_socket, message, strlen(message), 0) == -1) {
            perror("Sending failed.");
            exit(EXIT_FAILURE);
        }
    }

    pthread_cancel(receive_thread);
    close(client_socket);
    cout << "Connection closed." << endl;
    return NULL;
}

void* receive_function(void* arg) {
    while (1) {
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received == -1) {
            perror("Receiving failed.");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_received] = '\0';
        cout << "Server response: " << buffer << endl;
        cout << "Enter message (or 'exit' to quit):" << endl;
    }
}

int main() {
    sockaddr_in server_address = sockaddr_in();

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        perror("Client socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connected to server." << endl;

    pthread_create(&send_thread, NULL, send_function, NULL);
    pthread_create(&receive_thread, NULL, receive_function, NULL);

    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    return 0;
}
