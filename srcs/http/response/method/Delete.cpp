#include "Delete.hpp"

Delete::Delete(void) {}

Delete::~Delete(void) {}

void Delete::doMethod(void) {
}

void Delete::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Delete::getHasBody() {
	return (this->_hasBody);
}