#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include "ServerBlock.hpp"
#include <list>

class RootBlock {
private:
	std::list<ServerBlock> _serverBlockList;
public:
	RootBlock(void);
	RootBlock(const RootBlock& other);
	RootBlock&
	operator=(const RootBlock& other);
	~RootBlock(void);
};

#endif