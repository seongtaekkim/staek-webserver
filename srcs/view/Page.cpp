#include "Page.hpp"
#include "../http/response/HTTPStatus.hpp"
#include "../util/Base.hpp"
#include "../main.hpp"

Page::Page(void) {}

Page::~Page(void) {}

const std::string Page::resolve(const HTTPStatus::StateType& httpStatus) {

	const std::string line = Base::toString(httpStatus.first, 10) + " " + httpStatus.second;
	const std::string html = ""
			"<html>\n"
			"	<head>\n"
			"		<title>" + line + "</title>\n"
			"	</head>\n"
			"	<body bgcolor=\"gray\">\n"
			"		<center><h1>" + line + "</h1></center>\n"
			"		<center>" APPLICATION_NAME + "/" + APPLICATION_VERSION "</center>\n"
			"	</body>\n"
			"</html>\n";
	return (html);
}
