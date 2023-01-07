#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
int main()
{
    int sock;
    struct sockaddr_in broadcastAddr;
    char *broadcastIP;
    unsigned short broadcastPort;
    char *sendString;
    int broadcastPermission;
    unsigned int sendStringLen;

    char buffer[1000];
    broadcastIP = "10.0.2.255"; //broadcast address of network
    broadcastPort = 8080;
    sendString = "Hello from server!\n";

   sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    broadcastPermission = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission));

    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
    broadcastAddr.sin_port = htons(broadcastPort);

    sendStringLen = strlen(sendString);
    for (;;)
    {
    sendto(sock, sendString,sendStringLen , 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr));
        sleep(3);
    }
}


