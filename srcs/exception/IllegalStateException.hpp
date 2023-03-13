#ifndef ILLEGALSTATEEXCEPTION_HPP
#define ILLEGALSTATEEXCEPTION_HPP

#include "RuntimeException.hpp"

/**
 * @brief 부적절한 인수를 메서드에 전달할 경우 unchecked exception 발생.
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