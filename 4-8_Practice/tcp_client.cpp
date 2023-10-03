#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define ADDRESS "127.0.0.1"
#define MAX_LEN 1024

using namespace std;

int main() {
    int socket_fd;
    string message;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address;
    char buffer[MAX_LEN];

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ADDRESS);

    int connectResult = connect(socket_fd, (sockaddr*) &server_address, sizeof(server_address));

    if (connectResult == -1) {
        perror("Connection failed.");
        exit(EXIT_FAILURE);
    }

    message = "Message from client.";

    strncpy(buffer, message.c_str(), MAX_LEN);

    if (send(socket_fd, buffer, MAX_LEN, 0) == -1) {
        perror("Sending failed.");
        exit(EXIT_FAILURE);
    }

    memset(buffer, 0, MAX_LEN);

    if (recv(socket_fd, buffer, MAX_LEN, 0) == -1) {
        perror("Receiving failed.");
        exit(EXIT_FAILURE);
    }

    cout << "Received: " << buffer << endl;

    close(socket_fd);
    return 0;
}