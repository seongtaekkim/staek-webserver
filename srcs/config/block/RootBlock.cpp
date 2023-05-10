#include "RootBlock.hpp"
#include <iostream>

RootBlock::RootBlock(void) {}

RootBlock::~RootBlock(void) {}

RootBlock::RootBlock(const RootBlock& other) {}
RootBlock& RootBlock::operator=(const RootBlock& other) {return (*this);}

void RootBlock::setMaxConnection(std::string str) {
	this->_maxConnection = (int)::strtol(str.c_str(), NULL, 10);
}

void RootBlock::setWorkerCnt(std::string str) {
	this->_workerCnt = (int)::strtol(str.c_str(), NULL, 10)	;
}

int RootBlock::getMaxConnection(void) const {
	return (this->_maxConnection);
}

int RootBlock::getWorkerCnt(void) const {
	return (this->_workerCnt);
}

void RootBlock::setInclude(std::string str) {
	this->_include = str;
}

std::string RootBlock::getInclude(void) const {
	return (this->_include);
}

#include <map>
void RootBlock::check(std::string key, std::string value) {


	typedef void (RootBlock::*FuncPointer)(std::string);
	typedef std::map<std::string, FuncPointer> FuncMap;
	typedef FuncMap::iterator FuncMapIter;
	FuncMap							_map;
	FuncMapIter						_pos;

	_map["worker_connections"] = &RootBlock::setMaxConnection;
	_map["worker_processes"] = &RootBlock::setWorkerCnt;
	_map["include"] = &RootBlock::setInclude;

		_pos = _map.find(key);
		if (_pos != _map.end()) {
			FuncPointer ptr = _pos->second;
			(this->*ptr)(value);
		}
	
}

void RootBlock::appendServerBlock(ServerBlock* serverBlock) {
	this->_serverBlockList.push_back(serverBlock);
}

 
std::list<ServerBlock*> RootBlock::ServerBlockList(void) {
	return (this->_serverBlockList);
}