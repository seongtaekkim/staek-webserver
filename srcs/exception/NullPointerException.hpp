#ifndef NULLPOINTEREXCEPTION_HPP
#define NULLPOINTEREXCEPTION_HPP

#include "RuntimeException.hpp"

/**
 * @brief Null Exception
 * @author seongtki
 * @date 2023.03.22
 */
class NullPointerException : public RuntimeException {
public:
	NullPointerException(void);
	NullPointerException(const std::string message);
	virtual ~NullPointerException(void) throw();
	NullPointerException(const NullPointerException& other);
	NullPointerException&
	operator=(const NullPointerException& other);
};

#endif