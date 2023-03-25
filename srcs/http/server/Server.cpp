#include "Server.hpp"

Server::Server(std::string host, int port, std::list<ServerBlock *> sb)
		: _host(host),
		_port(port),
		_serverBlocks(sb),
		_socket(Socket::create())
		//_clients(),
{}

void
Server::init(void) {
	this->_socket->bind();
	this->_socket->listen();
	this->_socket->setNonBlock();
}

Socket*
Server::getSocket(void) const {
	return (this->_socket);
}