#include "Post.hpp"
#include "Get.hpp"

Post::Post(void) {}

Post::~Post(void) {}

bool Post::doMethod(Request &req, Response &res, Client &cli) {
	File targetFile(req.targetFile());

	bool justCreated = false;
	std::string out;
	if (targetFile.exists()) {
		if (targetFile.isDir() || !targetFile.isFile()) {
			std::cout << "req.url().fullUrl()" << req.url().fullUrl() << std::endl;
			std::cout << Get::instance()->listing(req.url(), targetFile) << std::endl;
			res.body(Get::instance()->listing(req.url(), targetFile));
			res.header().allow("GET");
			res.status(HTTPStatus::STATE[HTTPStatus::METHOD_NOT_ALLOWED]);
			return (true);
		}
	} else {
		try {
			targetFile.create();
			// res.headers().contentLocation(targetFile.path());
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