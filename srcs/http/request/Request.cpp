#include "Request.hpp"

typedef std::map<std::string, std::vector<std::string> >	headers_table;

/* 
	OCCF
*/

Request::Request() {}

Request::Request(const Request& __copy)
{
	_reqString = __copy._reqString;
	_requestLine = __copy._requestLine;
	_headers = __copy._headers;
	_body = __copy._body;
}

Request	Request::operator=(const Request& __copy)
{
	if (this != &__copy)
	{
		_reqString = __copy._reqString;
		_requestLine = __copy._requestLine;
		_headers = __copy._headers;
		_body = __copy._body;
	}
	return (*this);
}

Request::~Request() {}

/*
	Member functions
*/

Request::Request(std::string __reqString)
: _reqString(__reqString)
{
	_requestLine = RequestParser::parseRequestLine(_reqString.getRequestLine());
	_headers = RequestParser::parseHeaders(_reqString.getHeaders());
	if (_headers._headers["Transfer-Encoding"].size() == 0)
		_isChunked = false;
	else
		_isChunked = _headers._headers["Transfer-Encoding"][0] == "chunked";
	_body = _isChunked ? RequestParser::parseBody(_reqString.getBody()) : _reqString.getBody();
}

RequestString	Request::getReqString() { return (_reqString); }
RequestLine		Request::getRequestLine() { return (_requestLine); }
RequestHeaders	Request::getHeaders() { return (_headers); }

e_method		Request::method() { return (_requestLine._method); }
std::string		Request::uri() { return (_requestLine._uri); }
float			Request::version() { return (_requestLine._version); }
headers_table	Request::headers() { return (_headers._headers); }
std::string		Request::body() { return (_body); }
size_t			Request::header_count() { return (_headers._headerCount); }