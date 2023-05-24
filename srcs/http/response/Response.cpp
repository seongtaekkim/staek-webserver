#include "Response.hpp"
#include "../../config/Config.hpp"
#include "../SHTTP.hpp"
#include "../../util/Time.hpp"

Response::Response(void) : _body(), _state(INIT), _isEnd(false) {}

Response::Response(const Response& other) {
	if (this != &other) {
		this->_body = other._body;
		this->_cgiExtension = other._cgiExtension;
		this->_header = other._header;
		this->_headString = other._headString;
		this->_isEnd = other._isEnd;
		this->_state = other._state;
		this->_status = other._status;
	}
}

Response& Response::operator=(const Response& other) {
	if (this != &other) {
		this->_body = other._body;
		this->_cgiExtension = other._cgiExtension;
		this->_header = other._header;
		this->_headString = other._headString;
		this->_isEnd = other._isEnd;
		this->_state = other._state;
		this->_status = other._status;
	}
	return (*this);
}

Response::~Response(void) {
	ReleaseResource::pointer(this->_body);
}

bool Response::store(Storage& buffer) {
	if (!_isEnd)
		return (false);

	switch (_state) {
		case INIT:
			_state = HEADER;
		case HEADER:
			_state = BODY;
		case BODY:
		{
			_headString.append(StatusLine(_status).response());
			_headString.append(SHTTP::CRLF);
			_headString.append(header().format());
			_headString.append("Date: ");
			_headString.append(Time::NOW().format(SHTTP::DATEFORMAT));
			_headString.append(SHTTP::CRLF);
			_headString.append("Server: ");
			_headString.append(APPLICATION_NAME);	
			_headString.append(SHTTP::CRLF);
			_headString.append(SHTTP::CRLF);
			buffer.store(_headString);
			if (this->_body)
				this->_body->store(buffer);
			return (false);
		}
	}
	return (true);
}

IBody* Response::body(void) const {
	return (this->_body);
}

void Response::body(IBody* body) {
	this->_body = body;
}

void Response::body(const std::string str) {
	this->body(new ResponseByString(str));
	header().contentLength(str.length());
	this->end();
}

void Response::status(HTTPStatus::StateType& status) {
	this->_status = status;
}

HTTPStatus::StateType& Response::status(void) {
	return (this->_status);
}

Header& Response::header(void) {
	return (this->_header);
}

void Response::end(void) {
	this->_isEnd = true;
}

bool Response::isEnd(void) const {
	return (this->_isEnd);
}

int Response::state(void) const {
	return (this->_state);
}

void Response::cgiExtension(std::string str) {
	this->_cgiExtension = str;
}

std::string Response::cgiExtension(void) const {
	return (this->_cgiExtension);
}