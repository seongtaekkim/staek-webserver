#include "Get.hpp"

Get::Get(void) {}

Get::~Get(void) {}


#include "../../../file/File.hpp"
#include <list>
std::string sampleListing(File file)
{
	const std::string &directory = file.path();

	std::string out = ""
			"<html>\n"
			"	<head>\n"
			"		<title>Listing of " + directory + "</title>\n"
			"	</head>\n"
			"	<body>\n";

	std::list<File> files = file.list();
	for (std::list<File>::iterator it = files.begin(); it != files.end(); it++)
	{
		std::string name(it->name());
		if (it->isDir())
			name += '/';
		std::string path(file.path());
		if (path.empty())
			path += '/';
		path += name;
		out += std::string("<a href=\"") + path + "\">" + name + "</a><br>\n";
	}

	out += ""
			"	</body>\n"
			"</html>\n";

	return (out);
}

std::string sample() {
std::string str;
// str.append("GET / HTTP/1.1");
// str.append("\nUser-Agent: test");
// str.append("\nAccept: */*");
// str.append("\nHost: localhost:8080");
// str.append("\nAccept-Encoding: gzip, deflate, br");
// str.append("\nConnection: keep-alive");
 
// str.append("\nHTTP/1.1 200 OK");

str.append("\nContent-Length: 1092");
str.append("\nContent-Type: text/html");
str.append("\nDate: Thu, 30 Mar 2023 19:00:10 GMT");
str.append("\nServer: webserv\r\n\r\n");


File f("./");
str.append(sampleListing(f));
// str.append("<html>");
// str.append("<head>");
// str.append("<title>Listing of /</title>");
// str.append("</head>");
// str.append("<body>");
// str.append("test");
// str.append("</body>");
// str.append("</html>");
// std::cout << str << std::endl;

// std::cout << "str size : " << str.length() << std::endl;
return str;
}

#include "../../../util/Storage.hpp"
void Get::doMethod(Request &req, Response &res, Client &cli) {
	std::string ret = sample();
	Storage s;
	s.store(ret);

	// if (targetFile.isDirectory()) {
		// if (!request.listing())
			// res.status(*HTTPStatus::NOT_FOUND);
		// else
		{
			std::cout << "get domethod" << std::endl;
			// res.body(ret);
			// res.headers().html();
			res.status(HTTPStatus::STATE[HTTPStatus::OK]);
			res.store(s);

		}

	// }

	res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
}

void Get::setHasBody(bool hasbody) {
	this->_hasBody = hasbody;
}

bool Get::getHasBody() {
	return (this->_hasBody);
}