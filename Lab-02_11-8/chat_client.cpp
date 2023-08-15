#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
using namespace std;

int main() {
     int client_socket;
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

     if (
        connect(
            client_socket, 
            (sockaddr *) &server_address,  
            sizeof(server_address)
        ) == -1) {
         perror("Connection failed");
         exit(EXIT_FAILURE);
     }

     cout << "Connected to server." << endl;

     char message[BUFFER_SIZE];

     while (1) {
         cout << "Enter message (or 'exit' to quit):" << endl;
         fgets(message, BUFFER_SIZE, stdin);
         
         if (strcmp(message, "exit\n") == 0) {
             break;
         }

         if (send(client_socket, message, BUFFER_SIZE, 0) == -1) {
            perror("Sending failed.");
            exit(EXIT_FAILURE);
        }
     }

     close(client_socket);
     printf("Connection closed.\n");
     return 0;
}