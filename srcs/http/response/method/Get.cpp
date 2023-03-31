#include "Get.hpp"

Get::Get(void) {}

Get::~Get(void) {}

void Get::doMethod(void) {
	
}

void Get::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Get::getHasBody() {
	return (this->_hasBody);
}