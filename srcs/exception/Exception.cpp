#include "Exception.hpp"

Exception::Exception(void) {}
Exception::~Exception(void) throw() {}
Exception::Exception(const std::string& message) : _message(message) {}
Exception::Exception(const Exception& other) : _message(other._message) {}

Exception& Exception::operator=(const Exception& other) {
	if (this != &other)
		this->_message = other._message;
	return (*this);
}

const std::string&
Exception::message() const {
	return (this->_message);
}

const char*
Exception::what(void) const throw() {
	return (this->_message.c_str());
}