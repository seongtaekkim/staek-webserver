#ifndef IOEXCEPTION_HPP
#define IOEXCEPTION_HPP

#include "Exception.hpp"

/**
 * @brief IOException
 * @details errno에 매핑되는 메세지를 출력할 수 있다.
 * @author seongtki
 * @date 2023.03.22
 */
class IOException : public Exception {
private:
	int	_errorno;
public:
	IOException(void);
	IOException(const std::string message, int errorno);
	IOException(const IOException& other);
	virtual ~IOException() throw();
	IOException& operator=(const IOException& other);
	int errorno() const;
};

#endif