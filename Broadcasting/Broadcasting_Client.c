#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<unistd.h>

#include <string.h>
#define MAXRECVSTRING 255

int main()
{
    int sock;
    struct sockaddr_in broadcastAddr;
    unsigned short broadcastPort;
    char recvString[MAXRECVSTRING+1];
    int recvStringLen;

    broadcastPort = 8080;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    broadcastAddr.sin_port = htons(broadcastPort);

    bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr));
    recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0);
    recvString[recvStringLen] = '\0';
    printf("Received: %s\n", recvString);
    close(sock);
return 0;
}


