#include "TooBigHeaderException.hpp"

TooBigHeaderException::TooBigHeaderException() : RuntimeException() {}

TooBigHeaderException::TooBigHeaderException(const std::string& msg) : RuntimeException(msg) {}

TooBigHeaderException::TooBigHeaderException(const TooBigHeaderException &other) : RuntimeException(other) {}

TooBigHeaderException::~TooBigHeaderException() throw() {}

TooBigHeaderException& TooBigHeaderException::operator=(const TooBigHeaderException &other) {
	RuntimeException::operator=(other);
	return (*this);
}
