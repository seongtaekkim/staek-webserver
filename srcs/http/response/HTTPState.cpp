#include "HTTPState.hpp"

HTTPStatus::HTTPStatus() {}

HTTPStatus::HTTPStatus(int code, std::string codeNm) : _code(code), _codeNm(codeNm) {}

HTTPStatus::StateMap HTTPStatus::STATE = init();

int HTTPStatus::code() const {
	return (this->_code);
}

std::string HTTPStatus::codeNm() const {
	return (this->_codeNm);
}