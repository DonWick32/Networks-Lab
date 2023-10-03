#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
AF_INET,SOCK_STREAM,0);
 sa.sin_family=AF_INET;
 sa.sin_addr.s_addr=INADDR_ANY;
 sa.sin_port=60018;
 i=bind(sockfd,#include <arpa/inet.h>
#include <netdb.h>

int main() {
int sockfd,fd1,i;
char buf[100];
struct sockaddr_in sa,ta1;
sockfd=socket((struct sockaddr *)&sa,sizeof(sa));
 listen(sockfd,5);
 socklen_t length = sizeof(sa);
 fd1=accept(sockfd, (struct sockaddr *) &ta1, &length);
 for(i=0; i < 100; i++) buf[i] = '\0';
                        strcpy(buf,"Message from server (Nitish)");
                        send(fd1, buf, 100, 0);
for(i=0; i < 100; i++) buf[i] = '\0';
                        recv(fd1, buf, 100, 0);
                        printf("%s\n", buf);

        close(fd1);
        return 0;
 }