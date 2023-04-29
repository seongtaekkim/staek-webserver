#ifndef RESPONSEBYSTRING_HPP
#define RESPONSEBYSTRING_HPP

#include "IBody.hpp"

class ResponseByString : public IBody {
private:
	std::string _string;
public:
	ResponseByString(void);
	ResponseByString(const std::string& string);
	ResponseByString(const ResponseByString& other);
	ResponseByString& operator=(const ResponseByString& other);
	virtual ~ResponseByString(void);
	
	virtual bool store(Storage& storage);
	virtual bool isEnd(void);
};

#endif
