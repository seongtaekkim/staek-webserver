#ifndef IDENTITYENCODER_HPP
#define IDENTITYENCODER_HPP

#include "IHTTPBodyEncoder.hpp"
#include <string>

class IdentityEncoder : public IHTTPBodyEncoder {
private:
	IdentityEncoder(const IdentityEncoder& other);
	IdentityEncoder& operator=(const IdentityEncoder& other);

public:
	IdentityEncoder(void);
	virtual ~IdentityEncoder(void);
	std::string encode(const std::string& input);
};

#endif
