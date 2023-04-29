#include "ResponseByString.hpp"

ResponseByString::ResponseByString() : _string() {}

ResponseByString::ResponseByString(const std::string &content) 
	: _string(content) {}

ResponseByString::~ResponseByString(void) {}

ResponseByString::ResponseByString(const ResponseByString &other)
	: _string(other._string) {}

ResponseByString& ResponseByString::operator=(const ResponseByString& other) {
	if (this != &other)
		_string = other._string;
	return (*this);
}

bool ResponseByString::store(Storage& storage) {
	storage.store(_string);
	return (true);
}

bool ResponseByString::isEnd(void) {
	return (true);
}