#ifndef INETADDRESS_HPP
#define INETADDRESS_HPP

#include <string>

class InetAddress {
private:
	int			_port;
	std::string _address;
public:
	InetAddress(const InetAddress& other);
	InetAddress& operator=(const InetAddress& other);
	InetAddress(void);
	~InetAddress(void);
	int port() const;
	std::string address() const;
};

#endif