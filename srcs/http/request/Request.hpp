#ifndef REQUEST_HPP
#define REQUEST_HPP
#include "RequestString.hpp"
#include "RequestParser.hpp"
#include "RequestLine.hpp"
#include "RequestHeaders.hpp"
#include "../../file/File.hpp"
#include "../response/StatusLine.hpp"
#include "../URL.hpp"
// #include "../response/method/Method.hpp"
// #include "../../config/block/LocationBlock.hpp"
// #include "../../config/block/ServerBlock.hpp"
// #include "../Header.hpp"

/**
 * @brief HTTP 요청 메시지 string을 파싱하여 저장
 * @details string과 파싱된 결과를 각각 저장
 * @author chanhyle
 * @date 2023.03.29
 */
class Request {

public:
	typedef std::map<std::string, std::vector<std::string> >	headers_table;

private:
	std::string				_resource;
	RequestString			_reqString;
	RequestLine				_requestLine;
	RequestHeaders			_headers;
	std::string				_body;
	bool					_isChunked;

	StatusLine				_statusLine;
	URL						_url;
	// HTTPHeaderFields m_headers;
	// const Method*			_method;
	// const ServerBlock*		_serverBlock;
	// const LocationBlock*	_locationBlock;

public:
	Request(void);
	Request(const StatusLine& statusLine, const URL& url);
	// Request(const StatusLine& statusLine, const URL& url, const Header& header);
	~Request(void);
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

	File targetFile(void);
	std::string root(void) const;

	const URL& url(void) const;
};

#endif
