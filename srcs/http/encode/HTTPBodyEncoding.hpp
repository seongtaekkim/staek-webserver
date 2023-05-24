#ifndef HTTPBODYENCODING_HPP
#define HTTPBODYENCODING_HPP

#include "../decode/ChunkDecoder.hpp"
#include "HTTPBodyEncoding.hpp"
#include "../decode/IdentityDecoder.hpp"
#include "../Header.hpp"
#include <string>
#include "../../util/Base.hpp"

class IHTTPBodyDecoder;

class HTTPBodyEncoding {
private:
	HTTPBodyEncoding(void);
	HTTPBodyEncoding(const HTTPBodyEncoding& other);
	HTTPBodyEncoding& operator=(const HTTPBodyEncoding& other);

public:
	virtual ~HTTPBodyEncoding(void);

public:
	static IHTTPBodyDecoder* decodeSelector(const Header &header);
};

#endif
