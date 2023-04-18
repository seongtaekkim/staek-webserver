#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
// #include "ServContext.hpp"
// #include "Common.hpp"
#include "Socket.hpp"
#include "Client.hpp"
#include "../../config/block/ServerBlock.hpp"
#include "RWCallback.hpp"
#include <map>

/**
 * @brief 서버 정보관리
 * @details Socket, host, port
 * @author seongtki
 * @date 2023.03.23
 */
class Client;
class Socket;
class Server : RWCallback {
private:
	Socket*						_socket;
	std::string					_host;
	int							_port;
	std::list<ServerBlock *>	_serverBlocks;
	std::map<int, Client*>		_clients;
	
	//int			_maxFd;
	//int			_readFd;
	//int			_writeFd;
	Server(void);
public:
	virtual ~Server(void);
	Server(std::string host, int port,  std::list<ServerBlock *> sb);
	void init(void);
	Socket* getSocket(void) const;
	std::string getHost() const;
	int getPort() const;
	std::list<ServerBlock *> getServerBlocks() const;
	void close();
	Socket* connect(Socket* serverSocket);
	void disconnect(Client& client);
	std::map<int, Client*> clients();
	bool recv(FileDescriptor &fd);
};

#endif