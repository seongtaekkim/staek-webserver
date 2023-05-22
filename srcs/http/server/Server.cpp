#include "Server.hpp"
#include "../../iom/KqueueManage.hpp"
#include "../../address/InetAddress.hpp"
#include "../../util/Time.hpp"

Server::Server(std::string host, int port, std::list<ServerBlock *> sb)
		: _host(host),
		_port(port),
		_serverBlocks(sb),
		_socket(Socket::create())
		//_clients(),
{
	if (this->_port == 0) {
		this->_port = SHTTP::DEFAULT_PORT;
	}
	if (_host.empty()) {
		this->_host = SHTTP::DEFAULT_HOST;
	}
}

Server::~Server(void) {
	delete _socket;
}

void Server::init(void) {
	this->_socket->reuse();
	this->_socket->setNonBlock();
	this->_socket->bind(this->_port);
	this->_socket->listen();
	std::cout << "server socket : " << this->_socket->getFd() << std::endl;
	KqueueManage::instance().setEvent(this->_socket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	std::cout << " started " << std::endl;
	KqueueManage::instance().create(*this->_socket, *this);
}	

Socket*
Server::getSocket(void) const {
	return (this->_socket);
}

void Server::close(void) {
	this->_socket->close();
}

std::map<int, Client*> Server::clients() {
	return (this->_clients);
}

Socket* Server::connect(Socket* serverSocket) {
	// Socket &serverSocket = static_cast<Socket&>(fd);

	InetAddress socketAddress;
	Socket *socket = serverSocket->accept(&socketAddress);

	std::cout << "Accepted: "  << " (fd=" << socket->getFd() << ')' << std::endl;

	socket->setNonBlock();
	Client& client = *(new Client(socketAddress, *this, *socket));
	this->_clients.insert(std::make_pair(socket->getFd(), &client));
	// this->_clients.push_back(&client);

	return (socket);
}

void Server::disconnect(Client& client) {
	_clients.erase(client.socket().getFd());
	std::cout << "disconnect " << std::endl;
}


bool Server::recv(FileDescriptor &fd) {
	std::cout << "accete fd : " << fd.getFd() << std::endl;

	Socket &serverSocket = static_cast<Socket&>(fd);
	this->connect(&serverSocket);

	// if (Client::INSTANCE_COUNT > Configuration::instance().rootBlock().maxActiveClient().orElse(RootBlock::DEFAULT_MAX_ACTIVE_CLIENT))
		// Client::setUnavailable(httpClient);

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
		std::cout<<"*************Server::checkTimeout : " << (*it).first<< " " << client.lastTime()  << std::endl;

		it++;	
		if (client.cgiWrite() && client.cgiWrite()->timeoutTouch()) {
            std::cout<<" client.cgiWrite()->timeoutTouch(" << std::endl;
			client.updateTime();
		} else if (client.lastTime() + timeout < now) {
			this->clients().erase(client.socket().getFd());
			delete this->clients()[client.socket().getFd()];
			KqueueManage::instance().delEvent(client.socket().getFd());
		}
	}
}
