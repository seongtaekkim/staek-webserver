#include "RuntimeException.hpp"

RuntimeException::RuntimeException(void) : Exception() {}

RuntimeException::RuntimeException(const RuntimeException &other) : Exception(other) {}

RuntimeException&
RuntimeException::operator=(const RuntimeException& other) {
	Exception::operator=(other);
	return (*this);
}

RuntimeException::~RuntimeException(void) throw() {}

RuntimeException::RuntimeException(const std::string message) : Exception(message) {}