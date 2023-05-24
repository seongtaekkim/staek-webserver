#include "SHTTP.hpp"

const char			SHTTP::SP = ' ';
const std::string	SHTTP::CRLF = "\r\n";
const int			SHTTP::MAJOR = 1;
const int			SHTTP::MINOR = 1;
const char*			SHTTP::DATEFORMAT = "%a, %d %b %Y %H:%M:%S GMT";
const int			SHTTP::DEFAULT_READSIZE = 3276800;
const std::string	SHTTP::APPLICATION_NAME = "webserv";
const int			SHTTP::DEFAULT_MAX_ACTIVE_CLIENT = 200;
const int			SHTTP::DEFAULT_TIMEOUT = 30;
const std::string	SHTTP::DEFAULT_TMP_FILE = "/tmp/" + SHTTP::APPLICATION_NAME;
const int			SHTTP::DEFAULT_PORT = 8080;
const std::string	SHTTP::DEFAULT_HOST = "localhost";
const unsigned long	SHTTP::DEFAULT_MAX_BODY_SIZE = 1 * 1024 * 1024;


std::string SHTTP::VERSION() {
	std::stringstream version ;
	version << "HTTP/" << SHTTP::MAJOR << "." << SHTTP::MINOR;
	return (version.str());
}