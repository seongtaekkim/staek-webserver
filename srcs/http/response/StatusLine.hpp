#ifndef STATUSLINE_HPP
#define STATUSLINE_HPP

#include <sstream>
#include "HTTPStatus.hpp"
#include "../SHTTP.hpp"

// HTTP/1.1 200 OK
class StatusLine {
private:
	std::string				_version;
	HTTPStatus::StateType	_status;
public:
	StatusLine(void);
	StatusLine(HTTPStatus::StateType status);
	StatusLine(const StatusLine& other);
	StatusLine& operator=(const StatusLine& other);
	~StatusLine(void);
	std::string version(void);
	HTTPStatus::StateType status(void);
	std::string response(void);

};

#endif