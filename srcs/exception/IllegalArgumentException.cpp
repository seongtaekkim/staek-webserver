#include "IllegalArgumentException.hpp"

IllegalArgumentException::IllegalArgumentException(void) : RuntimeException() {}
IllegalArgumentException::IllegalArgumentException(const std::string message) : RuntimeException(message) {}
IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException& other) : RuntimeException(other) {}
IllegalArgumentException&
IllegalArgumentException::operator=(const IllegalArgumentException& other) {
	RuntimeException::operator=(other);
	return (*this);
}
IllegalArgumentException::~IllegalArgumentException(void) throw() {}