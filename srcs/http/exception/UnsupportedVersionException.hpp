#ifndef UNSUPPORTEDVERSIONEXCEPTION_HPP
#define UNSUPPORTEDVERSIONEXCEPTION_HPP

#include "../../exception/RuntimeException.hpp"
#include <string>

class UnsupportedVersionException : public RuntimeException {
	public:
		UnsupportedVersionException(void);
		UnsupportedVersionException(const std::string& msg);
		UnsupportedVersionException(const UnsupportedVersionException& other);

		virtual ~UnsupportedVersionException() throw();
		UnsupportedVersionException& operator=(const UnsupportedVersionException &other);
};

#endif
