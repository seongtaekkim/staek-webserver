#include "UnsupportedVersionException.hpp"

UnsupportedVersionException::UnsupportedVersionException() : RuntimeException() {}

UnsupportedVersionException::UnsupportedVersionException(const std::string &msg) : RuntimeException(msg) {}

UnsupportedVersionException::UnsupportedVersionException(const UnsupportedVersionException &other) : RuntimeException(other) {}

UnsupportedVersionException::~UnsupportedVersionException() throw() {}

UnsupportedVersionException& UnsupportedVersionException::operator=(const UnsupportedVersionException &other) {
	RuntimeException::operator=(other);
	return (*this);
}