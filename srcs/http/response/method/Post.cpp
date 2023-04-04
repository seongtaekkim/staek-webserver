#include "Post.hpp"

Post::Post(void) {}

Post::~Post(void) {}

void Post::doMethod(Request &req, Response &res, Client &cli) {
}

void Post::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Post::getHasBody() {
	return (this->_hasBody);
}