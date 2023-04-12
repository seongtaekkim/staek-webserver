#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <list>
#include <string>
#include "ServerBlock.hpp"

class RootBlock {
public:
	// typedef void (RootBlock::*FuncPointer)(std::string);
	// typedef std::map<std::string, FuncPointer> FuncMap;
	// typedef FuncMap::iterator FuncMapIter;
	// FuncMap							_map;
	// FuncMapIter						_pos;
	
	

private:
	std::list<ServerBlock*>			_serverBlockList;
	int								_maxConnection;
	int								_workerCnt;
	std::string						_include;
public:
	RootBlock(const RootBlock& other);
	RootBlock& operator=(const RootBlock& other);
	RootBlock(void);
	~RootBlock(void);
	
	void setMaxConnection(std::string str);
	void setWorkerCnt(std::string str);
	void setInclude(std::string str);
	int getMaxConnection(void) const;
	int getWorkerCnt(void) const;
	std::string getInclude(void) const;
	void appendServerBlock(ServerBlock* serverBlock);
	std::list<ServerBlock*> ServerBlockList(void);
	void check(std::string key, std::string value);

};

#endif