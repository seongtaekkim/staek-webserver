#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../../file/File.hpp"
#include "../response/StatusLine.hpp"
#include "../URL.hpp"
#include "../Header.hpp"
#include "../../config/Config.hpp"
#include <iostream>

/**
 * @brief HTTP 요청 메시지 string을 파싱하여 저장
 * @details string과 파싱된 결과를 각각 저장
 * @author chanhyle
 * @date 2023.03.29
 */
class Request {

private:
	std::string				_resource;
	std::string				_body;
	bool					_isChunked;
	StatusLine				_statusLine;
	URL						_url;
	Header					_header;
	// const Method*			_method;
	const ServerBlock*		_serverBlock;
	const LocationBlock*	_locationBlock;

public:
	Request(void);
	Request(const Header& header, const StatusLine& statusLine, const URL& url);
	~Request(void);
	Request(const Request& __copy);
	Request	operator=(const Request& __copy);

	std::string		body();
	File			targetFile(void);
	std::string		root(void) const;
	const URL&		url(void) const;
	const std::string resource() const;
	void resource(const std::string& resource);

	void serverBlock(const ServerBlock& serverBlock);
	const ServerBlock* serverBlock(void) const;
	void locationBlock(const LocationBlock& locationBlock);
	const LocationBlock* locationBlock(void) const;
};
#endif
