#ifndef SERVERBLOCK
#define SERVERBLOCK

#include <list>
#include <string>
#include <iostream>
#include "LocationBlock.hpp"
#include "../Reader.hpp"

class ServerBlock {
private:
	int									_listen;
	std::string 						_serverName;
	std::string							_root;
	std::pair<std::string, std::string>	_cgi;
	std::list<LocationBlock*>			_locationBlockList;
	// std::pair<std::string, std::string>	_errorPage;
public:
	ServerBlock(void);
	ServerBlock(const ServerBlock& other);
	ServerBlock& operator=(const ServerBlock& other);
	~ServerBlock(void);

	void check(std::string key, std::string value);

	void setListen(std::string str);
	int getListen(void);
	void setServerName(std::string str);
	std::string getServerName(void);
	void setRoot(std::string str);
	std::string getRoot(void);
	void setCgi(std::string str);
	std::pair<std::string, std::string> getCgi(void);

	void appendLocationBlock(LocationBlock* locationBlock);
	std::list<LocationBlock*> LocationBlockList(void);
};

#endif
