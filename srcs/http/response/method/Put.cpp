#include "../HTTPState.hpp"
#include "Put.hpp"
#include "PutTask.hpp"
#include <sys/fcntl.h>

Put::Put(void) {}

Put::Put(const Put& other) {
	(void)other;
}

Put::~Put(void) {}

Put& Put::operator =(const Put &other) {
	(void)other;
	return (*this);
}

bool Put::doMethod(Request& req, Response& res, Client& cli) {
	File targetFile(req.targetFile());

	bool justCreated = false;
	if (targetFile.exists()) {
		if (targetFile.isDir() || !targetFile.isFile()) {
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
			return (true);
		}
	} else {
		try {
			targetFile.create();
			justCreated = true;
		} catch (Exception& exception) {
			res.status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
			return (true);
		}
	}
	
	FileDescriptor &fd = *targetFile.open(O_WRONLY | O_TRUNC, 0777);
	cli.fileWrite(*(new PutTask(cli, fd, justCreated)));
	return (false);
}

void Put::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Put::getHasBody() {
	return (this->_hasBody);
}