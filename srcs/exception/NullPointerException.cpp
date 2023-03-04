#include "NullPointerException.hpp"

NullPointerException::NullPointerException(void) : RuntimeException() {}
NullPointerException::NullPointerException(const std::string message) : RuntimeException(message) {}
NullPointerException::~NullPointerException(void) throw() {}
NullPointerException::NullPointerException(const NullPointerException& other) : RuntimeException(other) {}
NullPointerException&
NullPointerException::operator=(const NullPointerException& other) {
	RuntimeException::operator=(other);
	return (*this);
}