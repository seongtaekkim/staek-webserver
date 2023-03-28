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

std::size_t Storage::capacity(void) {

}

std::string& Storage::store(std::string str) {
	this->_storage += str;
}

std::string& Storage::storage(void) {
	return (this->_storage);
}