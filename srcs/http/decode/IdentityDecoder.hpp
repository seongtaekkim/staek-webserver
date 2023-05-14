#ifndef IDENTITYDECODER_HPP
#define IDENTITYDECODER_HPP

#include "IHTTPBodyDecoder.hpp"
#include "../../exception/Exception.hpp"

class IdentityDecoder : public IHTTPBodyDecoder {
private:
	bool m_isAllocated;
	long long m_contentLength;
	long long m_consumed;

private:
	IdentityDecoder(void);
	IdentityDecoder(const IdentityDecoder& other);
	IdentityDecoder& operator=(const IdentityDecoder& other);

public:
	IdentityDecoder(bool isAllocated, long long contentLength);
	virtual ~IdentityDecoder(void);

	bool consume(const std::string &in, std::string &out, size_t &consumed, bool max);
	void cleanup();
};

#endif
