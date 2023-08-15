#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int client_count = 0;
int client_sockets[MAX_CLIENTS];
pthread_t threads[MAX_CLIENTS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
     int client_socket = *((int *)arg);
     char buffer[BUFFER_SIZE];

     while (1) {
         int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
         if (bytes_received <= 0) {
             pthread_mutex_lock(&mutex);
             for (int i = 0; i < client_count; i++) {
                 if (client_sockets[i] == client_socket) {
                     client_count--;
                     for (int j = i; j < client_count; j++) {
                         client_sockets[j] = client_sockets[j + 1];
                     }
                     break;
                 }
             }
             pthread_mutex_unlock(&mutex);
             close(client_socket);
             pthread_exit(NULL);
         }

         buffer[bytes_received] = '\0';
         printf("Received: %s", buffer);

         pthread_mutex_lock(&mutex);
         for (int i = 0; i < client_count; i++) {
             if (client_sockets[i] != client_socket) {
                 send(client_sockets[i], buffer, bytes_received, 0);
             }
         }
         pthread_mutex_unlock(&mutex);
     }
}

int main() {
     int server_socket;
     struct sockaddr_in server_addr;

     server_socket = socket(AF_INET, SOCK_STREAM, 0);
     if (server_socket == -1) {
         perror("Socket creation failed");
         exit(EXIT_FAILURE);
     }

     memset(&server_addr, 0, sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_addr.s_addr = INADDR_ANY;
     server_addr.sin_port = htons(PORT);

     if (bind(server_socket, (struct sockaddr *)&server_addr,  
sizeof(server_addr)) == -1) {
         perror("Binding failed");
         exit(EXIT_FAILURE);
     }

     if (listen(server_socket, MAX_CLIENTS) == -1) {
         perror("Listening failed");
         exit(EXIT_FAILURE);
     }

     printf("Server listening on port %d...\n", PORT);

     while (1) {
         if (client_count < MAX_CLIENTS) {
             int client_socket = accept(server_socket, NULL, NULL);
             if (client_socket == -1) {
                 perror("Accepting connection failed");
                 continue;
             }

             pthread_mutex_lock(&mutex);
             client_sockets[client_count] = client_socket;
             client_count++;
             pthread_mutex_unlock(&mutex);

             pthread_create(&threads[client_count - 1], NULL,  
handle_client, &client_socket);
         }
     }

     close(server_socket);
     return 0;
}

