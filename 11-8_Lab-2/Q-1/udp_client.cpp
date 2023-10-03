#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 4952
#define ADDRESS "10.1.22.59"
using namespace std;

int main(){
    int socket_fd;
    string message;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd == -1){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address = sockaddr_in();

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ADDRESS);

    cout << "Enter message:" << endl;
    getline(cin, message);

    int bytes = sendto(
        socket_fd,
        message.c_str(),
        message.size(),
        0,
        (const sockaddr*) &server_address,
        sizeof(server_address)
    );

    if (bytes == -1){
        perror("Message sending failed.");
        exit(EXIT_FAILURE);
    }

    cout << "Message of " << bytes << " bytes has been sent to " << inet_ntoa(server_address.sin_addr) << endl;
    close(socket_fd);
    return 0;
}