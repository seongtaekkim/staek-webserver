#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <poll.h>
#include <iostream>

#define PORT 20162
#define BUFFER_SIZE 100
#define LISTEN_QUEUE_SIZE 5
#define theNumberOfFDs 100

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        printf("Usage: %s IPv4-address\n", argv[0]);
        return -1;
    }
 
    struct sockaddr_in connectSocket;
 
    memset(&connectSocket, 0, sizeof(connectSocket));
 
    connectSocket.sin_family = AF_INET;
    inet_aton(argv[1], (struct in_addr*) &connectSocket.sin_addr.s_addr);
    connectSocket.sin_port = htons(PORT);
 
    int connectFD = socket(AF_INET, SOCK_STREAM, 0);
 
    if (connect(connectFD, (struct sockaddr*) &connectSocket, sizeof(connectSocket)) == -1) 
    {
        printf("Can not connect.\n");
        return -1;
    }
 
    else 
    {
        int readBytes, writtenBytes;
        char sendBuffer[BUFFER_SIZE];
        char receiveBuffer[BUFFER_SIZE];
 
    //while(1)
    //{
            //서버에 문자열을 보낸 뒤 서버가 보낸 echo를 받아 출력.
            printf("input :: ");
 
            fgets(sendBuffer,BUFFER_SIZE,stdin);
 
            write(connectFD, sendBuffer, strlen(sendBuffer));
            
 
            readBytes = read(connectFD, receiveBuffer, BUFFER_SIZE);
            printf("%d bytes read\n", readBytes);
            receiveBuffer[readBytes] = '\0';
        
            fputs(receiveBuffer, stdout);
            fflush(stdout);
     //}
        
        
        
    }
 
    close(connectFD);
    return 0;
 
    
}    