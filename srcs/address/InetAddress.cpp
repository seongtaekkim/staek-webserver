#include "InetAddress.hpp"

InetAddress::InetAddress(void) {}
InetAddress::~InetAddress(void) {}

InetAddress::InetAddress(const InetAddress& other) : _address(other.address()), _port(other.port()) {

}
InetAddress& InetAddress::operator=(const InetAddress& other) {
	if (&other != this) {
		this->_address = other.address();
		this->_port = other.port();
	}
	return (*this);
}

int InetAddress::port() const {
	return (this->_port);
}
std::string InetAddress::address() const {
	return (this->_address);
}

