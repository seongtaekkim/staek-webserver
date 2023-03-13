#include "IllegalStateException.hpp"

IllegalStateException::IllegalStateException(void) : RuntimeException() {}
IllegalStateException::IllegalStateException(const std::string message) : RuntimeException(message) {}
IllegalStateException::IllegalStateException(const IllegalStateException& other) : RuntimeException(other) {}
IllegalStateException&
IllegalStateException::operator=(const IllegalStateException& other) {
	RuntimeException::operator=(other);
	return (*this);
}
IllegalStateException::~IllegalStateException(void) throw() {}