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
#define SERVER_PORT 8000
#define BUFFER_SIZE 1024
using namespace std;

int main() {
     int client_socket;
     struct sockaddr_in server_addr;

     client_socket = socket(AF_INET, SOCK_STREAM, 0);
     if (client_socket == -1) {
         perror("Socket creation failed");
         exit(EXIT_FAILURE);
     }

     memset(&server_addr, 0, sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(SERVER_PORT);
     if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
         perror("Invalid address");
         exit(EXIT_FAILURE);
     }

     if (connect(client_socket, (struct sockaddr *)&server_addr,  
sizeof(server_addr)) == -1) {
         perror("Connection failed");
         exit(EXIT_FAILURE);
     }

     printf("Connected to server.\n");

     char message[BUFFER_SIZE];
     while (1) {
        memset(message, 0, BUFFER_SIZE);
         printf("Enter message (or 'exit' to quit): ");
         fgets(message, sizeof(message), stdin);
         if (strcmp(message, "exit\n") == 0) {
             break;
         }
        //  cout << "HI" << endl;
         send(client_socket, message, strlen(message), 0);
        // cout << "HI" << endl;
        memset(message, 0, BUFFER_SIZE);
         recv(client_socket, message, BUFFER_SIZE, 0);
        cout << "Received from server: " << message << endl;
     }

     close(client_socket);
     printf("Connection closed.\n");
     return 0;
}