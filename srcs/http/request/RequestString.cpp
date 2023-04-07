#include "RequestString.hpp"

/*
	OCCF
*/

RequestString::RequestString() {}

RequestString::RequestString(const RequestString& __copy)
{
	this->_originString = __copy._originString;
	this->_requestLine = __copy._requestLine;
	this->_headers = __copy._headers;
	this->_body = __copy._body;
}

RequestString	RequestString::operator=(const RequestString& __copy)
{
	if (this != &__copy)
	{
		this->_originString = __copy._originString;
		this->_requestLine = __copy._requestLine;
		this->_headers = __copy._headers;
		this->_body = __copy._body;
	}
	return (*this);
}

RequestString::~RequestString() {}

/*
	Member functions
*/

RequestString::RequestString(std::string __reqString)
: _originString(__reqString), _requestLine(""), _headers(""), _body("")
{
	// 예외 처리 필요(Parsing exception) e.g. SP, CRLF가 없을 때
	size_t			requestLineIndex;
	size_t			headersIndex;

	requestLineIndex = getRequestLineString(__reqString);
	headersIndex = getHeadersString(__reqString, requestLineIndex);
	getBodyString(__reqString, headersIndex);
}

// 유효하지 않은 request-line의 수신자는 400(Bad Request) 오류 또는 301(Moved Permanently) 리다이렉트로 응답
size_t	RequestString::getRequestLineString(std::string __reqString)
{
	size_t						index;
	std::vector<std::string>	sp_splited;

	index = __reqString.find(CRLF) + 2;
	_requestLine = __reqString.substr(0, index);
	sp_splited = RequestParser::split(_requestLine, SP);
	if (sp_splited.size() != 3)
		throw IllegalStateException("HTTP Request start line SP error.");
	return (index);
}

size_t	RequestString::getHeadersString(std::string __reqString, size_t __requestLineIndex)
{
	size_t	index = __requestLineIndex;

	do
	{
		index = __reqString.find(CRLF, index) + 2;
		if (index == std::string::npos + 2 || index == __reqString.size())
			throw IllegalStateException("HTTP Request headers CRLF error.");
	}
	while (__reqString.compare(index, 2, CRLF) != 0);
	_headers = __reqString.substr(__requestLineIndex, index - __requestLineIndex);
	return (index);
}

size_t	RequestString::getBodyString(std::string __reqString, size_t __headersIndex)
{
	_body = __reqString.substr(__headersIndex + 2, __reqString.size() - (__headersIndex + 2));
	return (__reqString.size());
}

std::string		RequestString::getOrigString() { return (_originString); }
std::string		RequestString::getRequestLine() { return (_requestLine); }
std::string		RequestString::getHeaders() { return (_headers); }
std::string		RequestString::getBody() { return (_body); }