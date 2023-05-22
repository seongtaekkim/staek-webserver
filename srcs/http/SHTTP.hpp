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
	static const int			DEFAULT_READSIZE;
	static const std::string	APPLICATION_NAME;
	static const int 			DEFAULT_MAX_ACTIVE_CLIENT;
	static const int 			DEFAULT_TIMEOUT;
	static const std::string	DEFAULT_TMP_FILE;
	static const int			DEFAULT_PORT;
	static const std::string	DEFAULT_HOST;
};

#endif