#ifndef PAYLOADTOOBIGEXCEPTION_HPP
#define PAYLOADTOOBIGEXCEPTION_HPP

#include "../../exception/RuntimeException.hpp"
#include <string>

class PayloadTooBigException : public RuntimeException {
public:
	PayloadTooBigException(void);
	PayloadTooBigException(const std::string& msg);
	PayloadTooBigException(const PayloadTooBigException& other);
	PayloadTooBigException& operator=(const PayloadTooBigException& other);
	virtual ~PayloadTooBigException() throw();
};

#endif
