#ifndef TOOBIGHEADEREXCEPTION_HPP
#define TOOBIGHEADEREXCEPTION_HPP

#include "../../exception/RuntimeException.hpp"
#include <string>

class TooBigHeaderException : public RuntimeException {
public:
	TooBigHeaderException(void);
	TooBigHeaderException(const std::string& msg);
	TooBigHeaderException(const TooBigHeaderException& other);
	virtual ~TooBigHeaderException(void) throw();
	TooBigHeaderException& operator=(const TooBigHeaderException &other);
};

#endif
