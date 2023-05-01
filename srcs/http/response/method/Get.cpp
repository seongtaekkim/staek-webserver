#include "Get.hpp"

Get::Get(void) {}

Get::~Get(void) {}


#include "../../../file/File.hpp"
#include <list>

std::string listing(const URL& url, const File& file) {
	const std::string &directory = url.path();

	std::string out = ""
			"<html>\n"
			"	<head>\n"
			"		<title>Listing of " + directory + "</title>\n"
			"	</head>\n"
			"	<body>\n";

	std::list<File> files = file.list();
	for (std::list<File>::iterator it = files.begin(); it != files.end(); it++) {
		std::string name(it->name());

		if (it->isDir())
			name += '/';

		std::string path(url.path());
		if (path.empty() || path.c_str()[path.length() - 1] != '/')
			path += '/';
		path += name;
		out += std::string("		<a href=\"") + path + "\">" + name + "</a><br>\n";
	}

	out += ""
			"	</body>\n"
			"</html>\n";

	return (out);
}

#include "../../../util/Storage.hpp"
#include "../../../util/Time.hpp"
#include "../../../config/Mime.hpp"
#include "../../../config/Config.hpp"
#include "../../../util/ReleaseResource.hpp"
#include "../ResponseByFile.hpp"

bool Get::doMethod(Request &req, Response &res, Client &cli) {


	File targetFile(req.targetFile());
	std::cout << "getgetget !!!!!!!!!!!!!!!" << std::endl;
	std::cout << targetFile.path() << std::endl;
	if (!targetFile.exists()) {
		res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		return (true);
	}

	if (targetFile.isFile()) {
		std::size_t contentLength = targetFile.size();
		// Time lastModified = targetFile.lastModified();
		
		Mime::MimeType contentType;

		std::string extension;
		
		std::cout << req.url().fullUrl() << std::endl;
		if (req.url().extension(extension)) {
			contentType = Config::instance().mime()->mimeMap()[extension];
		}
		std::cout << "extension : " << extension << std::endl;
		std::cout << "contentType : " << contentType.front() << std::endl;

		FileDescriptor *fd = NULL;
		try {
			fd = targetFile.open(O_RDONLY, 0666);
			res.body(new ResponseByFile(*fd, contentLength));
			// res.header().contentLength(contentLength);
			// res.headers().contentType(contentType);
			// response.headers().lastModified(lastModified);
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
		}
		catch (...) {
			ReleaseResource::pointer<FileDescriptor>(fd);
			throw;
		}
		return (true);
	}

	if (targetFile.isDir()) {
		// if (!request.listing())
			// res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		// else {
			res.body(listing(req.url(), targetFile));

			// res.string(listing(request.url(), targetFile)); 
			// res.headers().html(); // MIME_HTML = "text/html"; mime setting 
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
		// }
		return (true);
	}
	res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
	return (true);
}

void Get::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Get::getHasBody() {
	return (this->_hasBody);
}