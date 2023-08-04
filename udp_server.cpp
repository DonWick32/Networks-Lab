#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000
#define ADDRESS "127.0.0.1"
#define MAX_LEN 1024
using namespace std;

int main(){
    int socket_fd;
    string message;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd == -1){
        perror("Socket creation failed.");
        cout << "Socket creation failed." << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address = sockaddr_in();

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ADDRESS);

    if (
        bind(
            socket_fd,
            (const sockaddr*) &server_address,
            sizeof(server_address)
        ) == -1
    ){
        perror("Binding failed.");
        exit(EXIT_FAILURE);
    }

    sockaddr_in client_address;
    char *buffer;
    socklen_t client_address_size;

    int bytes = recvfrom(
        socket_fd,
        buffer,
        MAX_LEN,
        MSG_WAITALL,
        (sockaddr *) &client_address,
        &client_address_size
    );

    if (bytes == -1){
        perror("Message receiving failed.");
        exit(EXIT_FAILURE);
    }

    cout << "Got packet of size " <<  bytes <<"bytes from " << inet_ntoa(client_address.sin_addr) << endl;
    cout << buffer << endl;
    return 0;
}