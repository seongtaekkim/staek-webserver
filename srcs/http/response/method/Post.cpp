#include "Post.hpp"

Post::Post(void) {}

Post::~Post(void) {}

bool Post::doMethod(Request &req, Response &res, Client &cli) {
	return true;
}

void Post::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Post::getHasBody() {
	return (this->_hasBody);
}