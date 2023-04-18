#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../../file/FileDescriptor.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

// #define DEFAULT_PORT = 8080
// #define DEFAULT_BACKLOG = 1024
/*
port, backlog 받아와서 처리해야 함
*/

class Socket : public FileDescriptor {
public:
	static const int DEFAULT_BACKLOG = 100;
private:
	int _server_fd;
	static const bool _s_isReuse;
	Socket(void);
	Socket(const Socket& other);
	Socket& operator=(const Socket& other);
public:
	Socket(int fd);
	virtual ~Socket() throw();
	void reuse(void);
	void bind(void);
	void listen();
	Socket* accept();
	ssize_t recv(void *buffer, size_t length, int flags = 0);
	ssize_t send(const void *buffer, size_t length, int flags = 0);

public:
	static Socket* create(void);
};

#endif