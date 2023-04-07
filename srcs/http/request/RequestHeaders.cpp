#include "RequestHeaders.hpp"
#include <iostream>

/*
	OCCF
*/

RequestHeaders::RequestHeaders() : _headers(header_table()), _headerCount(0)
{
	std::string		list[] = {"Connection", "Content-Length", "Content-Type", "Cookie", "Host", "Keep-Alive", "Transfer-Encoding", "User-Agent"};

	for (int i = 0; i < sizeof(list) / sizeof(std::string); i++)
	{
		_headers.insert(std::make_pair(list[i], std::vector<std::string>()));
		_headerCount++;
	}
}

RequestHeaders::RequestHeaders(const RequestHeaders& __copy)
{
	_headers = __copy._headers;
	_headerCount = __copy._headerCount;
}

RequestHeaders	RequestHeaders::operator=(const RequestHeaders& __copy)
{
	if (this != &__copy)
	{
		_headers = __copy._headers;
		_headerCount = __copy._headerCount;
	}
	return (*this);
}

RequestHeaders::~RequestHeaders() {}

/*
	Member functions
*/

bool	RequestHeaders::keyExist(std::string __key)
{
	header_table::iterator	it = _headers.begin();
	header_table::iterator	ite = _headers.end();

	while (it != ite)
	{
		if (RequestParser::toupper(it->first) == RequestParser::toupper(__key))
			return true;
		it++;
	}
	return false;
}

void	RequestHeaders::insertHeader(std::string __fieldName, std::string __fieldValue)
{
	_headers.insert(std::make_pair(__fieldName, std::vector<std::string>()));
	_headers[__fieldName].push_back(__fieldValue);
	_headerCount++;
}

void	RequestHeaders::addFieldValue(std::string __fieldName, std::string __fieldValue)
{
	_headers[__fieldName].push_back(__fieldValue);
}
