#include "Response.hpp"
Response::Response(void) : _state(INIT) {}
Response::Response(const Response& other) {}
Response& Response::operator=(const Response& other) {
	return (*this);
}
Response::~Response(void) {}


bool Response::store(Storage& buffer) {
	// if (!m_ended)
	// 	return (false);

	// this->_body += buffer;

	switch (_state) {
		case INIT:
			_state = HEADER;
		case HEADER:
		{
			std::cout << "((((((((((((((((((((((((((((((((((" << _status.first << std::endl;
			// std::cout << buffer.storage()<< std::endl;
			std::cout << ")))))))))))))))))))))))))))))))" << std::endl;
			this->_body += StatusLine(_status).response();
			// this->_body += SHTTP::CRLF;
			// this->_body += SHTTP::CRLF;
			this->_body += buffer.storage();
			// // buffer.store(_header.format());
			// if (!m_body)
				// return (true);
			// this->_body += buffer.storage();
			_state = BODY;

			return (false);
		}

		case BODY:
		{
			std::cout << "resposne body !!!!!!!" << std::endl;
			buffer.store(this->_body);
				// m_state = S_FLUSH;

			return (false);
		}

		// case END:
			// return (buffer.empty());
	}
	return (true);
}

std::string Response::body(void) const {
	return (this->_body);
}

void Response::body(std::string body) {
	this->_body = body;
}

void Response::status(HTTPStatus::StateType& status) {
	this->_status = status;
}

HTTPStatus::StateType& Response::status(void) {
	return (this->_status);
}
