#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
// #include "ServContext.hpp"
// #include "Common.hpp"
#include "Socket.hpp"
#include "../../config/block/ServerBlock.hpp"
#include <list>

class Server {
private:
	Socket*					_socket;
	std::string				_host;
	int						_port;
	std::list<ServerBlock *>	_serverBlocks;
	// std::list<Client>		_clients;
	
	//int			_maxFd;
	//int			_readFd;
	//int			_writeFd;
	Server(void);
public:
	Server( std::string host, int port,  std::list<ServerBlock *> sb);
	void init(void);
	Socket* getSocket(void) const;
};

#endif