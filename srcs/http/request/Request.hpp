#ifndef REQUEST_HPP
#define REQUEST_HPP
#include "RequestString.hpp"
#include "RequestParser.hpp"
#include "RequestLine.hpp"
#include "RequestHeaders.hpp"

/**
 * @brief HTTP 요청 메시지 string을 파싱하여 저장
 * @details string과 파싱된 결과를 각각 저장
 * @author chanhyle
 * @date 2023.03.29
 */
class Request {

public:
	typedef std::map<std::string, std::vector<std::string> >	headers_table;

public:
	Request();
	~Request();
	Request(const Request& __copy);
	Request	operator=(const Request& __copy);

	Request(std::string __reqString);
	
	RequestString	getReqString();
	RequestLine		getRequestLine();
	RequestHeaders	getHeaders();

	e_method		method();
	std::string		uri();
	float			version();
	headers_table	headers();
	std::string		body();
	size_t			header_count();

private:
	RequestString			_reqString;
	RequestLine				_requestLine;
	RequestHeaders			_headers;
	std::string				_body;
	bool					_isChunked;
};

#endif
