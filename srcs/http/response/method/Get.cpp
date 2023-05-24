#include "Get.hpp"
#include "../../../util/Time.hpp"
#include "../../../util/Storage.hpp"
#include "../../../util/Time.hpp"
#include "../../../config/Mime.hpp"
#include "../../../config/Config.hpp"
#include "../../../util/ReleaseResource.hpp"
#include "../ResponseByFile.hpp"
#include "../../../file/File.hpp"
#include <list>

Get::Get(void) {}

Get::~Get(void) {}

std::string Get::listing(const URL& url, const File& file) {
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

bool Get::doMethod(Request &req, Response &res, Client &cli) {

	File targetFile(req.targetFile());

	if (res.body()) {
		return (true);
	}
	
	if (!targetFile.exists()) {
		res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		return (true);
	}

	if (targetFile.isFile()) {
		std::size_t contentLength = targetFile.size();
		Time lastupdate(targetFile.stat().st_mtimespec);
		std::string contentType;
		std::string extension;
		
		if (req.url().extension(extension)) {
			const Mime* mime = Config::instance().mime();
			contentType = mime->findType(extension);
		}
		FileDescriptor *fd = NULL;
		try {
			fd = targetFile.open(O_RDONLY, 0666);
			res.body(new ResponseByFile(*fd, contentLength, cli.server().getSocket()->getFd()));
			res.header().contentLength(contentLength);
			res.header().contentType(contentType);
			res.header().lastModified(lastupdate.formatTimeSpec(SHTTP::DATEFORMAT));
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
		}
		catch (...) {
			ReleaseResource::pointer<FileDescriptor>(fd);
			throw;
		}
		return (true);
	}

	if (targetFile.isDir()) {
		
		if (req.locationBlock()->getAutoindex().compare("on") != 0)
			res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		else {
			res.body(listing(req.url(), targetFile));
			res.header().mimeHTML(); 
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
		}
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