#include "../HTTPState.hpp"
#include "HEAD.hpp"

HEAD::HEAD(void) {}

HEAD::HEAD(const HEAD& other) {
	(void)other;
}

HEAD::~HEAD(void) {}

HEAD& HEAD::operator =(const HEAD &other) {
	(void)other;
	return (*this);
}

bool HEAD::doMethod(Request& req, Response& res, Client& cli) {

	File targetFile(req.targetFile());
	std::cout << "getgetget !!!!!!!!!!!!!!!" << std::endl;
	std::cout << targetFile.path() << std::endl;

	if (res.body()) {
		return (true);
	}
	
	if (!targetFile.exists()) {
		res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		return (true);
	}

	if (targetFile.isFile()) {
		std::size_t contentLength = targetFile.size();
		std::cout << "contentLength " << std::endl;
		res.header().contentLength(contentLength);
	}
	res.body(NULL);
	return (true);
}

void HEAD::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool HEAD::getHasBody() {
	return (this->_hasBody);
}