#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../../file/FileDescriptor.hpp"
#include "../../address/InetAddress.hpp"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

class Socket : public FileDescriptor {
public:
	static const int DEFAULT_BACKLOG = 100;
private:
	int _server_fd;
	static const bool _s_isReuse;
	InetAddress		_inetAddress;
	Socket(void);
	Socket(const Socket& other);
	Socket& operator=(const Socket& other);
public:
	Socket(int fd);
	virtual ~Socket() throw();
	void reuse(void);
	void bind(int port);
	void listen();
	Socket* accept(InetAddress *address) const;
	ssize_t recv(void *buffer, size_t length, int flags = 0);
	ssize_t send(const void *buffer, size_t length, int flags = 0);

public:
	static Socket* create(void);
};

#endif