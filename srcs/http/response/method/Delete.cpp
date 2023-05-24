#include "Delete.hpp"
#include "../make/MethodMaker.hpp"
#include "Method.hpp"
Delete::Delete(void) {}

Delete::~Delete(void) {}

bool Delete::doMethod(Request& req, Response& res, Client& cli) {
	(void)cli;
	File file(req.targetFile());

	if (!file.exists() || !file.isFile())
		res.status(HTTPStatus::STATE[HTTPStatus::NO_CONTENT]);
	else {
		try {
			file.remove();
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
		} catch (Exception& e) {
			res.status(HTTPStatus::STATE[HTTPStatus::ACCEPTED]);
		}
	}
	return (true);
}

void Delete::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Delete::getHasBody() {
	return (this->_hasBody);
}