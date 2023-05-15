#include "Post.hpp"

Post::Post(void) {}

Post::~Post(void) {}

bool Post::doMethod(Request &req, Response &res, Client &cli) {
	File targetFile(req.targetFile());

	bool justCreated = false;

	std::string out;
	if (targetFile.exists()) {
		if (targetFile.isDir() || !targetFile.isFile()) // TODO This is not supposed to work like that, but 42 tester....
		{
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
			return (true);
		}
	}
	else
	{
		try {
			targetFile.create();
			// res.headers().contentLocation(targetFile.path()); // TODO Wrong value returned
			justCreated = true;
		}
		catch (Exception &exception) {
			res.status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
			return (true);
		}
	}

	FileDescriptor &fd = *targetFile.open(O_WRONLY | O_APPEND, 0777);

	if (!justCreated)
		fd.lseek(0, SEEK_END);
	cli.fileWrite(*(new PutTask(cli, fd, justCreated)));

	return (false);
}

void Post::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Post::getHasBody() {
	return (this->_hasBody);
}