#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000
#define ADDRESS "127.0.0.1"
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

    cout << "Enter message:" << endl;
    getline(cin, message);

    int bytes = sendto(
        socket_fd,
        message.c_str(),
        message.size(),
        MSG_CONFIRM,
        (const sockaddr*) &server_address,
        sizeof(server_address)
    );

    if (bytes == -1){
        perror("Message sending failed.");
        exit(EXIT_FAILURE);
    }

    cout << "Message of " << bytes << " bytes has been sent to " << inet_ntoa(server_address.sin_addr) << endl;
    return 0;
}