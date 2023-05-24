#include "Storage.hpp"

Storage::Storage(void) : _maxSize(std::string::npos) {}

Storage::Storage(SizeType maxSize) : _maxSize(maxSize) {}

Storage::Storage(const Storage& other) {
	if (this != &other) {
		this->_storage = other._storage;
		this->_maxSize = other._maxSize;
	}
}

Storage& Storage::operator=(const Storage& other) {
	if (this != &other) {
		this->_storage = other._storage;
		this->_maxSize = other._maxSize;
	}
	return (*this);
}

Storage::~Storage(void) {
	this->clear();
}


void Storage::clear(void) {
	this->_storage.clear();
}

// maxsize - storage 
std::size_t Storage::capacity(void) {
	if (this->_storage.size() >= this->_maxSize)
		return (0);
	return (this->_maxSize - this->_storage.size());
}

std::string& Storage::store(std::string str) {
	this->_storage += str;
	return (this->_storage);
}

Storage& Storage::store(Storage& store) {
	this->_storage.append(store.storage());
	return (*this);
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

bool Storage::getC(char& c) const {
	if (this->_storage.empty())
		return (false);
	c = this->_storage[0];
	return (true);
}

bool Storage::next(void) {
	if (this->_storage.empty())
		return (false);
	this->_storage.erase(0, 1);
	return (true);
}