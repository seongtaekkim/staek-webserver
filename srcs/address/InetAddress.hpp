#ifndef INETADDRESS_HPP
#define INETADDRESS_HPP

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../exception/Exception.hpp"
#include "../util/Base.hpp"

class InetAddress {
private:
	int				_port;
	unsigned char 	_address[4];
public:
	InetAddress(const InetAddress& other);
	InetAddress(unsigned int address, int port);
	InetAddress& operator=(const InetAddress& other);
	InetAddress(void);
	~InetAddress(void);
	int port(void) const;
	std::string address(void) const;
public:
	static InetAddress create(const struct sockaddr* addr);
};

#endif