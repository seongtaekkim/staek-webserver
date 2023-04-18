#ifndef REQUESTSTRING_HPP
#define REQUESTSTRING_HPP

#include <string>
#include "../../exception/IllegalStateException.hpp"
#include "RequestParser.hpp"
#include "../SHTTP.hpp"

/**
 * @brief 파싱되지 않은 HTTP 요청 메시지 string을 저장
 * @details full string, 부분별 string을 각각 저장
 * @author chanhyle
 * @date 2023.03.24
 */
class RequestString {
private:
	size_t	getRequestLineString(std::string __reqString);
	size_t	getHeadersString(std::string __reqString, size_t __requestLineIndex);
	size_t	getBodyString(std::string __reqString, size_t __headersIndex);

public:
	RequestString();
	RequestString(const RequestString& __copy);
	RequestString	operator=(const RequestString& __copy);
	~RequestString();
	
	RequestString(std::string __reqString);

	std::string		getOrigString();
	std::string		getRequestLine();
	std::string		getHeaders();
	std::string		getBody();

private:
	std::string		_originString;
	std::string		_requestLine;
	std::string		_headers;
	std::string		_body;
};

// 정해진 규칙에 따라 string으로만 자르기
// 여기서 1차 오류 검증 => 어떤 부분까지 검증할 것인지 정할 것

#endif