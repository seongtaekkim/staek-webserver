#include "Server.hpp"
#include "../../iom/KqueueManage.hpp"
#include "../../address/InetAddress.hpp"

Server::Server(std::string host, int port, std::list<ServerBlock *> sb)
		: _host(host),
		_port(port),
		_serverBlocks(sb),
		_socket(Socket::create())
		//_clients(),
{}

Server::~Server(void) {}

void Server::init(void) {
	this->_socket->reuse();
	this->_socket->setNonBlock();
	this->_socket->bind();
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
	Socket *socket = serverSocket->accept();

	std::cout << "Accepted: " << socketAddress.address() << " (fd=" << socket->getFd() << ')' << std::endl;

	socket->setNonBlock();
	Client& client = *(new Client(socketAddress, *this, *socket));
	this->_clients.insert(std::make_pair(socket->getFd(), &client));
	// this->_clients.push_back(&client);

	return (socket);
}

void Server::disconnect(Client& client) {
	std::cout << "disconnect " << std::endl;
	this->_clients.clear();
}


bool Server::recv(FileDescriptor &fd) {
	std::cout << "accete fd : " << fd.getFd() << std::endl;

	Socket &serverSocket = static_cast<Socket&>(fd);
	this->connect(&serverSocket);

	// if (Client::INSTANCE_COUNT > Configuration::instance().rootBlock().maxActiveClient().orElse(RootBlock::DEFAULT_MAX_ACTIVE_CLIENT))
		// Client::setUnavailable(httpClient);

	return (false);
}
