#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket(), bind()
#include <sys/stat.h>
#include <arpa/inet.h> // htons()
#include <netinet/in.h>
#define MAX_BUF 1024

using namespace std;

// https://techlog.gurucat.net/292
// https://nowonbun.tistory.com/736
// https://bloodguy.tistory.com/entry/C-Linux-TCPIP-%EA%B0%84%EB%8B%A8%ED%95%9C-%EC%97%90%EC%BD%94%EC%84%9C%EB%B2%84
// sockaddr 구조체는 소켓의 주소를 담는 기본 구조체 역할을 한다.
// sockaddr을 그대로 사용할 경우, sa_data에 IP 주소와 Port 번호가 조합되어 있어 쓰거나 읽기 불편하다.
// sockaddr_in 구조체 : sockaddr 구조체에서 sa_family가 AF_INET인 경우 사용
// IPv4 주소와 포트를 따로 저장할 수 있기 떄문에 조금 더 편하게 사용할 수 있음

int socket(int domain, int type, int protocol);
// domain
// The domain parameter specifies a communications domain within which communication will take place
// e.g. PF_INET(Internet version 4 protocols)
// type
// The socket has the indicated type, which specifies the semantics of communication
// e.g. SOCK_STREAM : provides sequenced, reliable, two-way connection based byte streams(TCP)
// SOCK_DGRAM(datagrams, connectionless, UDP), SOCK_RAW(access to internal network protocols and interfaces)
// protocol
// e.g. IPPROTO_TCP(TCP, 연결 지향), IPPROTO_UDP(UDP, 비연결 지향)

int main(int argc, char **argv)
{
	int ssock, csock, maxfd, fd;
	socklen_t clen;
 
	struct sockaddr_in server_addr, client_addr[FD_SETSIZE];
	char szSendBuff[MAX_BUF];
	char szRecvBuff[MAX_BUF];

	fd_set readfds, allfds, writefds;
	int clientfds[FD_SETSIZE];
	struct timeval timeout;
	int	num_client = 0;

    // set the timeout value to 5 seconds
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

	// 서버 소켓 생성
	// When a socket is created with socket(2) it exists in a name space (address family)
	// socket is created in blocking mode by default.
	if ((ssock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket error: ");
		exit(1);
	}
	// std::cout << "ssock : " << ssock << std::endl;
	// fcntl(ssock, F_SETFL, O_NONBLOCK);
	clen=sizeof(client_addr[0]);
	// std::cout << clen << std::endl; // 16

	// 서버 구조체 초기화
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	// htonl, htons : host byte order to network byte order(Big Endian)
	// 데이터가 저장되는 방식에 있어서 CPU마다 차이가 발생. 원격 호스트에게 보낼 때는 htons(), 받았을 때는 ntohs()
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // (u_int32_t)0x00000000 => 0.0.0.0
	server_addr.sin_port = htons(atoi(argv[1])); // listen할 서버의 포트

	// bind
	// assigns a name to an unnamed socket.
	if (bind(ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind error : ");
		exit(1);
	}
	// bind error : : Address already in use
	// 클라이언트와 tcp 연결 중 서버 측에서 종료하고 같은 포트로 다시 열려고 했을 때
	// 연결이 끊어지면서 포트를 사용할 수 있는 것 아닌가? 해제하는데 시간이 걸리는가?

	// listen
	// If a connection request arrives with the queue full, the client may receive an error with an indication of ECONNREFUSED.
	// First, a socket is created with socket(2).
	// backlog : defines the maximum length for the queue of pending connections.
	// The backlog is currently limited (silently) to 128.
	if (listen(ssock, SOMAXCONN) < 0)
	{
		perror("listen error : ");
		exit(1);
	}

	// initialize the client fd set
    for (int i = 0; i < FD_SETSIZE; i++)
        clientfds[i] = -1;

	// set up the fd sets for select()
	FD_ZERO(&allfds);
    FD_SET(ssock, &allfds);
	maxfd = ssock;

	std::cout << "server started\n";
	
	// accept
	// csock = accept(ssock, (struct sockaddr *)&client_addr, &clen);
	// std::cout << "client : " << inet_ntoa(client_addr.sin_addr) << ":" << client_addr.sin_port << std::endl;

	// Accept 루프
	while (1)
	{
		// Send, Recv 버퍼 초기화
		memset(szSendBuff, 0, sizeof(szSendBuff));
		memset(szRecvBuff, 0, sizeof(szRecvBuff));

		readfds = allfds; // copy the fd set
		// select() examines the I/O descriptor sets whose addresses are passed in readfds, writefds, and errorfds
		// to see if some of their descriptors are ready for reading, are ready for writing, or have an exceptional condition pending, respectively.
		// If timeout is a null pointer, the select blocks indefinitely.
		// select() returns the total number of ready descriptors in all the sets.
        if (select(maxfd + 1, &readfds, NULL, NULL, &timeout) == -1)
		{
            perror("select");
            exit(EXIT_FAILURE);
        }
	
		for (fd = 0; fd <= maxfd; fd++)
		{
			if (FD_ISSET(fd, &readfds))
			{
                if (fd == ssock)
				{
                    // accept incoming connection
					// accept() extracts the first connection request on the queue of pending connections, 
					// creates a new socket with the same properties of socket, and allocates a new file descriptor for the socket.
					// If no pending connections are present on the queue, and the socket is not marked as non-blocking, accept() blocks the caller until a connection is present.
                    csock = accept(ssock, (struct sockaddr *)&client_addr[num_client], &clen);
                    if (csock == -1) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }

					// set stdin to non-blocking mode
					int flags = fcntl(ssock, F_GETFL, 0);
					if (flags == -1)
					{
						perror("fcntl");
						exit(EXIT_FAILURE);
					}
					if (fcntl(ssock, F_SETFL, flags | O_NONBLOCK) == -1)
					{
						perror("fcntl");
						exit(EXIT_FAILURE);
					}

					// add the new fd to the client fd set
                    for (num_client = 0; num_client < FD_SETSIZE; num_client++)
					{
                        if (clientfds[num_client] == -1)
						{
                            clientfds[num_client] = csock;
                            break;
                        }
                    }
					// clientfds[num_client] = csock;

                    // add the new fd to the fd set
                    FD_SET(csock, &allfds);
                    if (csock > maxfd)
                        maxfd = csock;

					std::cout << "[ SET CONNECTION ] " << inet_ntoa(client_addr[num_client].sin_addr) << ":" << client_addr[num_client].sin_port << std::endl;
					num_client++;
				}
				else
				{
					int i;
					for (i = 0; i < FD_SETSIZE; i++)
                        if (clientfds[i] == fd)
                            break;

					// Recv
					// read error : : Undefined error: 0(클라이언트가 tcp 접속을 끊을 때)
					if (recv(fd, szRecvBuff, MAX_BUF, 0) <= 0)
					{
						perror("read error : ");
						exit(1);
					}

					std::cout << "[ FROM : " << inet_ntoa(client_addr[i].sin_addr) << ":" << client_addr[i].sin_port << " ] " << szRecvBuff;

					// 보내기 버퍼 세팅
					strcpy(szSendBuff, szRecvBuff);
				
					// Send
					if (send(fd, szSendBuff, MAX_BUF, 0) <= 0)
					{
						perror("write error : ");
						exit(1);
					}
				}
			}
		}
	} // while (1)
	// close 처리 필요
	close(csock);
	close(ssock);
	return 0;
}