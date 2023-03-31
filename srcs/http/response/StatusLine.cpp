#include "StatusLine.hpp"

StatusLine::StatusLine(void) : _status(), _version(SHTTP::VERSION()) {}

StatusLine::StatusLine(HTTPStatus::StateType status) : _status(status), _version(SHTTP::VERSION()) {}

StatusLine::StatusLine(const StatusLine& other) {}

StatusLine& StatusLine::operator=(const StatusLine& other) {
	return (*this);
}

StatusLine::~StatusLine(void) {}

std::string StatusLine::version(void) {
	return (this->_version);
}

HTTPStatus::StateType
StatusLine::status(void) {
	return (this->_status);
}

//// HTTP/1.1 200 OK
std::string StatusLine::response(void) {
	std::stringstream ret;
	ret << this->version() << SHTTP::SP << this->status().first << SHTTP::SP << this->status().second;
	return (ret.str());
}