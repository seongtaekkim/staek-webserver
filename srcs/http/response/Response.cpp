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

			// fall through

		case HEADER:
		{
			buffer.store(StatusLine(_status).response());
			buffer.store(SHTTP::CRLF);
			// buffer.store(_header.format());
			buffer.store(SHTTP::CRLF);
			// if (!m_body)
				// return (true);
			this->_body += buffer.storage();
			_state = BODY;
			std::cout << "((((((((((((((((((((((((((((((((((" << StatusLine(_status).response()<< std::endl;
			std::cout << _status.first << _status.second << std::endl;
			std::cout << ")))))))))))))))))))))))))))))))" << std::endl;

			return (false);
		}

		case BODY:
		{
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
