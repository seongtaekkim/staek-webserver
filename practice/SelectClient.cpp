#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#define BUFSIZE 1024

void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char **argv)
{

	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;
	
	if(argc != 3)
	{
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == -1)
		error_handling("socket() error");
	if( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");
	while(1)
	{
		/* 서버 접속을 위한 소켓 생성 */ 
		/* 메시지 입력 전송*/
		fputs("전송할 메시지를 입력하세요(q to quit) : ", stdout);
		fgets(message, BUFSIZE, stdin);
		if(!strcmp(message, "q\n"))
			break;
		/* 소켓 연결 */
		write(sock, message, strlen(message));
		/* 메시지 수신 출력 */
		str_len = read(sock, message, BUFSIZE);
		message[str_len] = 0;
		printf("서버로부터 전송된 메시지 : %s", message);
	}
	close(sock); // 같은 소켓을 계속 사용하는 방법은?

	return 0;
}