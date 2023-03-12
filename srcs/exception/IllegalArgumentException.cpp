#include "IllegalArgumentException.hpp"

IlligalArgumentException::IlligalArgumentException(void) : RuntimeException() {}
IlligalArgumentException::IlligalArgumentException(const std::string message) : RuntimeException(message) {}
IlligalArgumentException::IlligalArgumentException(const IlligalArgumentException& other) : RuntimeException(other) {}
IlligalArgumentException&
IlligalArgumentException::operator=(const IlligalArgumentException& other) {
	RuntimeException::operator=(other);
	return (*this);
}
IlligalArgumentException::~IlligalArgumentException(void) throw() {}