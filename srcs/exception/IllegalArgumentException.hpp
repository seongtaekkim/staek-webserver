#ifndef ILLIGALARGUMENTEXCEPTION_HPP
#define ILLIGALARGUMENTEXCEPTION_HPP

#include "RuntimeException.hpp"

/**
 * @brief 객체상태가 메서드 호출을 처리하기 적절치 않을 경우 uncatched exception 발생.
 * @details message 를 인자로 받는다.
 * @author seongtki
 * @date 2023.03.23
 */
class IlligalArgumentException : public RuntimeException {
public:
	IlligalArgumentException(void);
	IlligalArgumentException(const std::string message);
	IlligalArgumentException(const IlligalArgumentException& other);
	IlligalArgumentException&
	operator=(const IlligalArgumentException& other);
	virtual ~IlligalArgumentException(void) throw();
};

#endif