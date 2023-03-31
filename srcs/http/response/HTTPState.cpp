#include "HTTPState.hpp"

HTTPStatus::HTTPStatus() {}

HTTPStatus::HTTPStatus(const HTTPStatus& other) {
	if (this != &other) {
		this->_code = other._code;
		this->_codeNm = other._codeNm;
	}
}

HTTPStatus& HTTPStatus::operator=(const HTTPStatus& other) {
	if (this != &other) {
		this->_code = other._code;
		this->_codeNm = other._codeNm;
	}
	return (*this);
}

HTTPStatus::~HTTPStatus(void) {}

HTTPStatus::StateMap HTTPStatus::STATE = init();

int HTTPStatus::code() const {
	return (this->_code);
}

std::string HTTPStatus::codeNm() const {
	return (this->_codeNm);
}