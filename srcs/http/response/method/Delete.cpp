#include "Delete.hpp"

Delete::Delete(void) {}

Delete::~Delete(void) {}

bool Delete::doMethod(Request &req, Response &res, Client &cli) {
	return (true);
}

void Delete::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Delete::getHasBody() {
	return (this->_hasBody);
}