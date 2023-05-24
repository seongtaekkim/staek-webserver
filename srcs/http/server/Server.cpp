#include "Server.hpp"
#include "../../iom/KqueueManage.hpp"
#include "../../address/InetAddress.hpp"
#include "../../util/Time.hpp"

Server::Server(std::string host, int port, std::list<ServerBlock *> sb)
		: _socket(Socket::create()), _host(host),
		_port(port),
		_serverBlocks(sb) {}

Server::~Server(void) {
	delete _socket;
}

void Server::init(void) {
	this->_socket->reuse();
	this->_socket->setNonBlock();
	this->_socket->bind(this->_port);
	this->_socket->listen();
	KqueueManage::instance().setEvent(this->_socket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	KqueueManage::instance().create(*this->_socket, *this, this->_socket->getFd());
}	

Socket* Server::getSocket(void) const {
	return (this->_socket);
}

void Server::close(void) {
	this->_socket->close();
}

std::map<int, Client*> Server::clients() {
	return (this->_clients);
}

Socket* Server::connect(Socket* serverSocket) {

	InetAddress socketAddress;
	Socket *socket = serverSocket->accept(&socketAddress);

	std::cout << "Accepted: "  << " (fd=" << socket->getFd() << ")" << std::endl;

	socket->setNonBlock();
	Client& client = *(new Client(socketAddress, *this, *socket));
	this->_clients.insert(std::make_pair(socket->getFd(), &client));

	if (Client::_s_connCnt > SHTTP::DEFAULT_MAX_ACTIVE_CLIENT) {
		Client::deny(*_clients.find(socket->getFd())->second);
    }
	return (socket);
}

void Server::disconnect(Client& client) {
	_clients.erase(client.socket().getFd());
}


bool Server::recv(FileDescriptor &fd) {
	(void)fd;
	return (false);
}

std::list<ServerBlock *> Server::getServerBlocks() const {
	return (this->_serverBlocks);
}

void Server::checkTimeout(void) {
	if (_clients.empty())
		return;

	unsigned long now = Time::currentSecond();
	unsigned long timeout = SHTTP::DEFAULT_TIMEOUT;

	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end();) {
		Client& client = *(*it).second;

		it++;	
		if (client.cgiWrite() && client.cgiWrite()->timeoutTouch()) {
			client.updateTime();
		} else if (client.lastTime() + timeout < now) {
			this->clients().erase(client.socket().getFd());
			delete this->clients()[client.socket().getFd()];
			KqueueManage::instance().delEvent(client.socket().getFd());
		}
	}
}

std::string Server::getHost() const {
	return (this->_host);
}

int Server::getPort() const {
	return (this->_port);
}