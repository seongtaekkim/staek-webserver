#include "Socket.hpp"

Socket::Socket(int fd) : FileDescriptor(fd) {}

Socket* Socket::create(void) {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw IOException("socket create : ", errno);
	return (new Socket(fd));
}

Socket::~Socket() throw() {}

void Socket::bind(void) {
	this->validateNotClosed();
    struct sockaddr_in server_addr;
    ::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(8080);

    if (::bind(this->getFd(), (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        throw IOException("bind error : ", errno);
}

void Socket::listen(void) {
	this->validateNotClosed();
    if (::listen(this->getFd(), 5) == -1)
        throw IOException("listen() error", errno);
}

void Socket::accept() {

}


void Socket::recv() {}

void Socket::send() {}