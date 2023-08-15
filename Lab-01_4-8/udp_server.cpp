#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8000
#define MAX_LEN 1024
using namespace std;

int main(){
    int socket_fd;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd == -1){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address = sockaddr_in();

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

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
    char* buffer = new char[MAX_LEN];

    socklen_t client_address_size = sizeof(client_address);

    int bytes = recvfrom(
        socket_fd,
        buffer,
        MAX_LEN,
        0,
        (sockaddr *) &client_address,
        &client_address_size
    );

    if (bytes == -1){
        perror("Message receiving failed.");
        exit(EXIT_FAILURE);
    }

    cout << "Got packet of size " <<  bytes <<" bytes from " << inet_ntoa(client_address.sin_addr) << endl;
    cout << "Message = " << buffer << endl;
    close(socket_fd);
    return 0;
}