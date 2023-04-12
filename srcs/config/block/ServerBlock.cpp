#include "ServerBlock.hpp"


ServerBlock::ServerBlock(void) {
	std::cout << "server block constructor " << std::endl;
}
ServerBlock::ServerBlock(const ServerBlock& other) {	std::cout << "server block copyconstructor " << std::endl;
}
ServerBlock& ServerBlock::operator=(const ServerBlock& other) { 
		std::cout << "server block assing constructor " << std::endl;

	return (*this);}
ServerBlock::~ServerBlock(void) {
		std::cout << "server block delete " << std::endl;

}

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

std::string ServerBlock::getRoot(void) {
	return (this->_root);
}

void ServerBlock::setCgi(std::string str) {
	int ret= 0 ;
	int firstWord = 0;

	ret = str.find_first_of(ISSPACE, firstWord);
	this->_cgi.first = str.substr(firstWord, ret - firstWord);
	this->_cgi.second = str.substr(ret);
}

std::pair<std::string, std::string> ServerBlock::getCgi(void) {
	return (this->_cgi);
}

void ServerBlock::appendLocationBlock(LocationBlock* locationBlock) {
	this->_locationBlockList.push_back(locationBlock);

}

std::list<LocationBlock*> ServerBlock::LocationBlockList(void) {
	return (this->_locationBlockList);
}

#include <map>
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

	_pos = _map.find(key);
	if (_pos != _map.end()) {
		FuncPointer ptr = _pos->second;
		(this->*ptr)(value);
	}

}
