#ifndef SERVERBLOCK
#define SERVERBLOCK

#include "LocationBlock.hpp"
#include <list>

class ServerBlock {
private:
	std::list<LocationBlock> locationBlockList;
public:
	ServerBlock(void);
	ServerBlock(const ServerBlock& other);
	ServerBlock&
	operator=(const ServerBlock& other);
};

#endif
