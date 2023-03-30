#include "Storage.hpp"


Storage::Storage(void) {}

Storage::Storage(const Storage& other) {}

Storage& Storage::operator=(const Storage& other) {return (*this);}

Storage::~Storage(void) {
	this->clear();
}


void Storage::clear(void) {
	this->_storage.clear();
}

// ?
std::size_t Storage::capacity(void) {
	return (1);
}

std::string& Storage::store(std::string str) {
	this->_storage += str;
	return (this->_storage);
}

std::string& Storage::store(const void* buf, std::size_t ret) {
	this->_storage.assign(static_cast<const char*>(buf), ret);
	return (this->_storage);
}

std::string& Storage::storage(void) {
	return (this->_storage);
}
std::size_t Storage::size(void) const {
	return (this->_storage.size());
}