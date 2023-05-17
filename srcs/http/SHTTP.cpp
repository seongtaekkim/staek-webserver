#include "SHTTP.hpp"

const char			SHTTP::SP = ' ';
const std::string	SHTTP::CRLF = "\r\n";
const int			SHTTP::MAJOR = 1;
const int			SHTTP::MINOR = 1;
const char*			SHTTP::DATEFORMAT = "%a, %d %b %Y %H:%M:%S GMT";
const int			SHTTP::DEFAULT_READSIZE = 32768;
const std::string	SHTTP::APPLICATION_NAME = "webserv";
const int			SHTTP::DEFAULT_MAX_ACTIVE_CLIENT = 60;
const int			SHTTP::DEFAULT_TIMEOUT = 30;

std::string SHTTP::VERSION() {
	std::stringstream version ;
	version << "HTTP/" << SHTTP::MAJOR << "." << SHTTP::MINOR;
	return (version.str());
}