#include "ServerBlock.hpp"
#include <map>

ServerBlock::ServerBlock(void) : _listen(0), _serverName(), _clientMaxBodySize(0) {}

ServerBlock::ServerBlock(const ServerBlock& other) {
	if (this != &other) {
		this->_cgi = other._cgi;
		this->_index = other._index;
		this->_listen = other._listen;
		this->_locationBlockList = other._locationBlockList;
		this->_root = other._root;
		this->_serverName = other._serverName;
	}
}

ServerBlock& ServerBlock::operator=(const ServerBlock& other) { 
	if (this != &other) {
		this->_cgi = other._cgi;
		this->_index = other._index;
		this->_listen = other._listen;
		this->_locationBlockList = other._locationBlockList;
		this->_root = other._root;
		this->_serverName = other._serverName;
	}
	return (*this);
}

ServerBlock::~ServerBlock(void) {}

void ServerBlock::setListen(std::string str) {
	this->_listen = (int)::strtol(str.c_str(), NULL, 10);
}

int ServerBlock::getListen(void) {
	return (this->_listen);
}

void ServerBlock::setServerName(std::string str) {
	this->_serverName = str;
}

std::string ServerBlock::getServerName(void) {
	return (this->_serverName);
}

void ServerBlock::setRoot(std::string str) {
	this->_root = str;
}

std::string ServerBlock::getRoot(void) const {
	return (this->_root);
}

void ServerBlock::setIndex(std::string str) {
	this->_index = str;
}

std::string ServerBlock::getIndex(void) const {
	return (this->_index);
}

void ServerBlock::setCgi(std::string str) {
	int ret= 0 ;
	int firstWord = 0;

	ret = str.find_first_of(ISSPACE, firstWord);
	this->_cgi.first = str.substr(firstWord, ret - firstWord);
	this->_cgi.second = str.substr(ret + 1);
}

void ServerBlock::setClientMaxBodySize(std::string str) {
	this->_clientMaxBodySize = (unsigned long)::strtol(str.c_str(), NULL, 10);
}

unsigned long ServerBlock::getClientMaxBodySize(void) const {
	return (this->_clientMaxBodySize);
}

std::pair<std::string, std::string> ServerBlock::getCgi(void) const {
	return (this->_cgi);
}

void ServerBlock::appendLocationBlock(LocationBlock* locationBlock) {
	this->_locationBlockList.push_back(locationBlock);
}

const std::list<LocationBlock*> ServerBlock::locationBlockList(void) const {
	return (this->_locationBlockList);
}

void ServerBlock::check(std::string key, std::string value) {


	typedef void (ServerBlock::*FuncPointer)(std::string);
	typedef std::map<std::string, FuncPointer> FuncMap;
	typedef FuncMap::iterator FuncMapIter;
	FuncMap							_map;
	FuncMapIter						_pos;

	_map["listen"] = &ServerBlock::setListen;
	_map["server_name"] = &ServerBlock::setServerName;
	_map["root"] = &ServerBlock::setRoot;
	_map["cgi"] = &ServerBlock::setCgi;
	_map["index"] = &ServerBlock::setIndex;
	_map["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;

	_pos = _map.find(key);
	if (_pos != _map.end()) {
		FuncPointer ptr = _pos->second;
		(this->*ptr)(value);
	}

}
