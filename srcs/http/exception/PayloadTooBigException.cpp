#include "PayloadTooBigException.hpp"

PayloadTooBigException::PayloadTooBigException() : RuntimeException() {}

PayloadTooBigException::PayloadTooBigException(const std::string& msg) : RuntimeException(msg) {}

PayloadTooBigException::PayloadTooBigException(const PayloadTooBigException &other) : RuntimeException(other) {}

PayloadTooBigException::~PayloadTooBigException() throw() {}

PayloadTooBigException& PayloadTooBigException::operator=(const PayloadTooBigException &other) {
	RuntimeException::operator=(other);
	return (*this);
}
