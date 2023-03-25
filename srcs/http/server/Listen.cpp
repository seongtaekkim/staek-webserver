#include "Listen.hpp"

Listen::Listen(std::string ip, int port) : _ip(ip), _port(port) {}
Listen::~Listen(void) throw() {}
std::string Listen::getIp() const {
	return (this->_ip);
}
int Listen::getPort() const {
	return (this->_port);
}