#include "SHTTP.hpp"

const char			SHTTP::SP = ' ';
const std::string	SHTTP::CRLF = "\r\n";
const int			SHTTP::MAJOR = 1;
const int			SHTTP::MINOR = 1;

std::string SHTTP::VERSION() {
	std::stringstream version ;
	version << "HTTP/" << SHTTP::MAJOR << "." << SHTTP::MINOR;
	return (version.str());
}