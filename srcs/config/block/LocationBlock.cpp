#include "LocationBlock.hpp"
#include <map>

LocationBlock::LocationBlock(void) : _clientMaxBodySize(0) {}
LocationBlock::LocationBlock(const LocationBlock& other) {
	if (this != &other) {
		this->_index = other._index;
		this->_path = other._path;
		this->_root = other._root;
	}
}

LocationBlock& LocationBlock::operator=(const LocationBlock& other) {
	if (this != &other) {
		this->_index = other._index;
		this->_path = other._path;
		this->_root = other._root;
	}
	return (*this);
}

LocationBlock::~LocationBlock(void) {}

void LocationBlock::setIndex(std::string str) {
	this->_index = str;
}

std::string LocationBlock::getIndex(void) const {
	return (this->_index);
}

void LocationBlock::setPath(std::string str) {
	this->_path = str;
}

std::string LocationBlock::getPath(void) const {
	return (this->_path);
}

void LocationBlock::setRoot(std::string str) {
	this->_root = str;
}

std::string LocationBlock::getRoot(void) const {
	return (this->_root);
}

void LocationBlock::setAutoindex(std::string str) {
	this->_autoindex = str;
}

std::string LocationBlock::getAutoindex(void) const {
	return (this->_autoindex);
}

void LocationBlock::setLimitExcept(std::string str) {
	this->_limitExcept = str;
}

std::string LocationBlock::getLimitExcept(void) const {
	return (this->_limitExcept);
}

void LocationBlock::setClientMaxBodySize(std::string str) {
	this->_clientMaxBodySize = (unsigned long)::strtol(str.c_str(), NULL, 10);
}

unsigned long LocationBlock::getClientMaxBodySize(void) const {
	return (this->_clientMaxBodySize);
}

void LocationBlock::check(std::string key, std::string value) {
	typedef void (LocationBlock::*FuncPointer)(std::string);
	typedef std::map<std::string, FuncPointer> FuncMap;
	typedef FuncMap::iterator FuncMapIter;
	FuncMap							_map;
	FuncMapIter						_pos;

	_map["index"] = &LocationBlock::setIndex;
	_map["path"] = &LocationBlock::setPath;
	_map["root"] = &LocationBlock::setRoot;
	_map["autoindex"] = &LocationBlock::setAutoindex;
	_map["limit_except"] = &LocationBlock::setLimitExcept;
	_map["client_max_body_size"] = &LocationBlock::setClientMaxBodySize;

	_pos = _map.find(key);
	if (_pos != _map.end()) {
		FuncPointer ptr = _pos->second;
		(this->*ptr)(value);
	}
}