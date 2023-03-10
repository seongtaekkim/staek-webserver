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


int main(int argc, char* argv[])
{
    int listenFD, connectFD;
    struct sockaddr_in listenSocket, connectSocket;
 
    socklen_t addrSz; // address size를 구할 변수
 
    int i;
    ssize_t strLen;
    char buf[BUFFER_SIZE];
 
    //if (argc != 2)
    //{
    //    printf("Usage : %s <port>\n", argv[0]);
    //    exit(1);
    //}
 
    listenFD = socket(PF_INET, SOCK_STREAM, 0);
	// std::cout << "listenFD : " << listenFD << std::endl;
    memset(&listenSocket, 0, sizeof(listenSocket));
 
    listenSocket.sin_family = AF_INET;
    listenSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    listenSocket.sin_port = htons(PORT);
 
 
    if (bind(listenFD, (struct sockaddr *) &listenSocket, sizeof(listenSocket)) == -1) {
        printf("Can not bind.\n");
        return -1;
    }
 
    if (listen(listenFD, LISTEN_QUEUE_SIZE) == -1) {
        printf("Listen fail.\n");
        return -1;
    }
 
    // pollfd 배열 구조체 생성
    struct pollfd pollFDs[theNumberOfFDs];
 
    pollFDs[0].fd = listenFD; // 0번째 배열에는 listen을 지정
    pollFDs[0].events = POLLIN; // 읽도록 만든다.
    pollFDs[0].revents = 0; // 처음에는 0으로 초기화 한다(아직 아무 일도 일어나지 않았으니)
 
    for (i = 1; i < theNumberOfFDs; i++)
        pollFDs[i].fd = -1; // 0번째 배열은 listen을 위한것이니 1번째부터 모두 -1로 초기화
 
    while (1)
    {
        int result = poll(pollFDs, theNumberOfFDs, -1); // -1 :: 무한 대기
 
        if (result > 0)
        {
            if (pollFDs[0].revents == POLLIN)
            {
                // 새로운 커넥션 요청이 들어왔을 때
                connectFD = accept(listenFD, (struct sockaddr*)&connectSocket, &addrSz);
				std::cout << "connectFD : " << connectFD <<  std::endl;
                for (i = 1; i < theNumberOfFDs; i++)
                {
                    if (pollFDs[i].fd == -1) // 비어있는 fd슬롯을 찾아서 넣어준다.
                    {
                        pollFDs[i].fd = connectFD;
                        pollFDs[i].events = POLLIN;
                        pollFDs[i].revents = 0;
                        break; // 모두 다 넣고 break를 통해 한번만 실행
                    }
                }
            }
 
            for (i = 1; i < theNumberOfFDs; i++)
            {
                switch (pollFDs[i].revents)
                {
                    // no events
                    case 0:
                        break; 
 
                    // data is ready
                    case POLLIN:
                        strLen = read(pollFDs[i].fd, buf, BUFFER_SIZE);
                        printf("%lu bytes read\n", strLen);
 
                        buf[strLen] = '\0';
                        fputs(buf, stdout);
                        fflush(stdout);
 
                        write(pollFDs[i].fd, buf, strlen(buf));
                        
                    
                    // 슬롯 초기화
                    default:
                        close(pollFDs[i].fd);
                        pollFDs[i].fd = -1;
                        pollFDs[i].revents = 0;
                        
                            
                }
            }
        }
 
        
    }
 
    close(listenFD);
 
    return 0;
}