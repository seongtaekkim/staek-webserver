#ifndef RUNTIMEEXCEPTION_HPP
#define RUNTIMEEXCEPTION_HPP

#include "Exception.hpp"
#include <string>

/**
 * @brief 예외처리(catch) 하지 않고 해당요청을 종료하는 최상위 Exception 정의
 * @author seongtki
 * @date 2023.03.22
 */
class RuntimeException : public Exception {
public:
	RuntimeException(void);
	RuntimeException(const RuntimeException &other);
	RuntimeException& operator=(const RuntimeException& other);
	virtual ~RuntimeException(void) throw();

	RuntimeException(const std::string message);
};

#endif