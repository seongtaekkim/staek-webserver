#include "Delete.hpp"

Delete::Delete(void) {}

Delete::~Delete(void) {}

void Delete::doMethod(Request &req, Response &res, Client &cli) {
}

void Delete::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Delete::getHasBody() {
	return (this->_hasBody);
}