#include "Post.hpp"

Post::Post(void) {}

Post::~Post(void) {}

void Post::doMethod(void) {
}

void Post::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Post::getHasBody() {
	return (this->_hasBody);
}