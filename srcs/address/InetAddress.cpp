#include "InetAddress.hpp"

InetAddress::InetAddress(void) {}
InetAddress::~InetAddress(void) {}

InetAddress::InetAddress(const InetAddress& other) : _address(), _port(other.port()) {
	std::memcpy(this->_address, other._address, sizeof(this->_address));
}

InetAddress& InetAddress::operator=(const InetAddress& other) {
	if (&other != this) {
		std::memcpy(this->_address, other._address, sizeof(this->_address));
		this->_port = other.port();
	}
	return (*this);
}

int InetAddress::port(void) const {
	return (this->_port);
}

InetAddress::InetAddress(unsigned int address, int port) {
	std::memcpy(this->_address, (unsigned char*)&address, sizeof(this->_address));
	this->_port = port;
}

InetAddress InetAddress::create(const struct sockaddr *addr) {
	switch (addr->sa_family)
	{
		case AF_INET:
		{
			const struct sockaddr_in *addr_in = (const struct sockaddr_in*)addr;
			return (InetAddress(addr_in->sin_addr.s_addr, addr_in->sin_port));
		}
		default:
			throw Exception("unsupported socket(only AF_INET) family: " + Base::toString(addr->sa_family, 10));
	}
}

std::string InetAddress::address(void) const {
	return (Base::toString((int)_address[0], 10) + "." + Base::toString((int)_address[1], 10) + "." + Base::toString((int)_address[2], 10) + "." + Base::toString((int)_address[3], 10));
}
