#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

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
         printf("Enter message (or 'exit' to quit): ");
         fgets(message, sizeof(message), stdin);
         if (strcmp(message, "exit\n") == 0) {
             break;
         }
         send(client_socket, message, strlen(message), 0);
     }

     close(client_socket);
     printf("Connection closed.\n");
     return 0;
}