#include "StatusLine.hpp"

StatusLine::StatusLine(void) : _version(SHTTP::VERSION()), _status() {}

StatusLine::StatusLine(HTTPStatus::StateType status) : _version(SHTTP::VERSION()), _status(status) {}

StatusLine::StatusLine(const StatusLine& other) {
	if (this != &other) {
		this->_status = other._status;
		this->_version = other._version;
	}	
}

StatusLine& StatusLine::operator=(const StatusLine& other) {
	if (this != &other) {
		this->_status = other._status;
		this->_version = other._version;
	}
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