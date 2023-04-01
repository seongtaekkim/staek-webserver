#ifndef SHTTP_HPP
#define SHTTP_HPP

#include <string>
#include <sstream>

class SHTTP {
public:
	static const char			SP;
	static const std::string	CRLF;
	static const int			MAJOR;
	static const int			MINOR;
	static std::string 			VERSION();
	static const char*			DATEFORMAT;
};

#endif