#ifndef IHTTPBODYENCODER_HPP
#define IHTTPBODYENCODER_HPP

#include <string>

class IHTTPBodyEncoder {
public:
	virtual ~IHTTPBodyEncoder(void);
	virtual std::string encode(const std::string &input) = 0;
	virtual void cleanup(void);
};

#endif
