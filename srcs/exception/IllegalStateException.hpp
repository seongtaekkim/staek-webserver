#ifndef ILLEGALSTATEEXCEPTION_HPP
#define ILLEGALSTATEEXCEPTION_HPP

#include "RuntimeException.hpp"

/**
 * @brief 객체상태가 메서드 호출을 처리하기 적절치 않을 경우 uncatched exception 발생.
 * @details message 를 인자로 받는다.
 * @author seongtki
 * @date 2023.03.23
 */
class IllegalStateException : public RuntimeException {
public:
	IllegalStateException(void);
	IllegalStateException(const std::string message);
	IllegalStateException(const IllegalStateException& other);
	IllegalStateException&
	operator=(const IllegalStateException& other);
	virtual ~IllegalStateException(void) throw();

};


#endif