#include "Response.hpp"
Response::Response(void) : _state(INIT), _isEnd(false), _body() {	std::cout << "response create" << std::endl;
}
Response::Response(const Response& other) {}
Response& Response::operator=(const Response& other) {
	return (*this);
}
Response::~Response(void) {
	std::cout << "response delete" << std::endl;
	ReleaseResource::pointer(this->_body);
}


#include "../SHTTP.hpp"
#include "../../util/Time.hpp"
bool Response::store(Storage& buffer) {
	// if (!m_ended)
	// 	return (false);

	// this->_body += buffer;

	switch (_state) {
		case INIT:
			_state = HEADER;
		case HEADER:
			_state = BODY;
		case BODY:
		{

			std::cout << "((((((((((((((((((((((((((((((((((" << _status.first << std::endl;
			_headString.append(StatusLine(_status).response());
			_headString.append(SHTTP::CRLF);
			
			_headString.append(header().format());
			// _headString.append("Content-Length: ");
			// _headString.append(this->header().get(Header::CONTENT_LENGTH));
			// _headString.append(SHTTP::CRLF);
			_headString.append("Content-Type: text/html");
			_headString.append(SHTTP::CRLF);
			_headString.append("Date: ");
			_headString.append(Time::NOW().format(SHTTP::DATEFORMAT));
			_headString.append(SHTTP::CRLF);
			_headString.append("Server: ");
			_headString.append(APPLICATION_NAME);
							_headString.append(SHTTP::CRLF);
				_headString.append(SHTTP::CRLF);
				// _headString.append(SHTTP::CRLF);
			buffer.store(_headString);
			std::cout << "================!!!=====================" << std::endl;
			if (this->_body) {
				this->_body->store(buffer);
			}
			else {
				_headString.append(SHTTP::CRLF);
				_headString.append(SHTTP::CRLF);
			}
			std::cout << buffer.storage() << std::endl;
			std::cout << ")))))))))))))))))))))))))))))))" << _state << std::endl;
			return (false);
		}

		// case END:
			// return (buffer.empty());
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