#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "ServContext.hpp"
#include "Common.hpp"


class Location {
private:
	std::string	rootPath;
	std::string	method;
public:
	Location(void);
};

// client accept info
class Listen {
private:
	std::string _ip;
	int			_port;

public:
	Listen(void);
	
};

class Server {
private:
	ServContext	_servContext;
	Fds			_fds;
	int			_maxFd;
	int			_readFd;
	int			_writeFd;
	//			servers
	Server(void);
public:
};

#endif