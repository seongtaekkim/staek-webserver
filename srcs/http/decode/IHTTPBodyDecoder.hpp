#ifndef IHTTPBODYDECODER_HPP
#define IHTTPBODYDECODER_HPP

#include <string>

class IHTTPBodyDecoder {
public:
	virtual ~IHTTPBodyDecoder(void);
	virtual bool parse(const std::string &in, std::string &out, size_t &consumed, bool max) = 0;
	std::string decode(const std::string &input, bool max);
	virtual void cleanup();

};

#endif
