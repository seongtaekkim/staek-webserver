#include "Response.hpp"
Response::Response(void) {}
Response::Response(const Response& other) {}
Response& Response::operator=(const Response& other) {
	return (*this);
}
Response::~Response(void) {}

void Response::setStatus(HTTPStatus::StateType state) {
	this->_status = state;
}

bool Response::store(std::string buffer) {
	// if (!m_ended)
	// 	return (false);

	this->_body += buffer;
		// m_state = S_FLUSH;
	return (true);
}

std::string Response::body(void) const {
	return (this->_body);
}