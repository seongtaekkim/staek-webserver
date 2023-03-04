#include "IOException.hpp"

IOException::IOException(void) : Exception(strerror(0)), _errorno(0) {}

IOException::IOException(const std::string message, int errorno) 
	: Exception(message + " : " + strerror(errorno)), _errorno(errorno) {}

IOException::IOException(const IOException& other) 
	: Exception(other), _errorno(other._errorno) {}

IOException::~IOException() throw() {}

IOException& IOException::operator=(const IOException& other) {
	Exception::operator=(other);
	this->_errorno = other._errorno;
	return (*this);
}

int IOException::errorno() const {
	return (_errorno);
}