#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../../file/FileDescriptor.hpp"
#include "Listen.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

// #define DEFAULT_PORT = 8080
// #define DEFAULT_BACKLOG = 1024s
/*
port, backlog 받아와서 처리해야 함
*/

class Socket : public FileDescriptor {
private:
	int _server_fd;
	Socket(void);
	Socket(const Socket& other);
	Socket& operator=(const Socket& other);
public:
	Socket(int fd);
	virtual ~Socket() throw();
	void bind(void);
	void listen();
	void accept();
	void recv();
	void send();

public:
	static Socket* create(void);
};

#endif