#ifndef SERVERBLOCK
#define SERVERBLOCK

#include <list>
#include <string>
#include <iostream>
#include "LocationBlock.hpp"
#include "../Reader.hpp"

class ServerBlock {
public:
	typedef std::pair<std::string, std::string> CgiType;
private:
	int									_listen;
	std::string 						_serverName;
	std::string							_root;
	CgiType								_cgi;
	std::list<LocationBlock*>			_locationBlockList;
	std::string							_index;

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
	std::string getRoot(void) const;
	void setIndex(std::string str);
	std::string getIndex(void) const;
	void setCgi(std::string str);
	std::pair<std::string, std::string> getCgi(void) const;

	void appendLocationBlock(LocationBlock* locationBlock);
	const std::list<LocationBlock*> locationBlockList(void) const;
};

#endif
