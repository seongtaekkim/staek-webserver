#include "LocationBlock.hpp"

LocationBlock::LocationBlock(void) {}
LocationBlock::LocationBlock(const LocationBlock& other) {

}
LocationBlock& LocationBlock::operator=(const LocationBlock& other) {
	return (*this);
}
LocationBlock::~LocationBlock(void) {}

void LocationBlock::setIndex(std::string str) {
	this->_index = str;
}

std::string LocationBlock::getIndex(void) {
	return (this->_index);
}

void LocationBlock::setPath(std::string str) {
	this->_path = str;
}

std::string LocationBlock::getPath(void) {
	return (this->_path);
}

#include <map>
void LocationBlock::check(std::string key, std::string value) {
	typedef void (LocationBlock::*FuncPointer)(std::string);
	typedef std::map<std::string, FuncPointer> FuncMap;
	typedef FuncMap::iterator FuncMapIter;
	FuncMap							_map;
	FuncMapIter						_pos;

	_map["index"] = &LocationBlock::setIndex;
	_map["path"] = &LocationBlock::setPath;
	// _map["limit_except"] = &LocationBlock::setListen;
	// _map["auth"] = &LocationBlock::setListen;
	// _map["auth"] = &LocationBlock::setListen;

	_pos = _map.find(key);
	if (_pos != _map.end()) {
		FuncPointer ptr = _pos->second;
		(this->*ptr)(value);
	}
}