#ifndef REQUESTPARSER_HPP
#define REQUESTPARSER_HPP

#include <string>
#include <cstdlib>
#include "RequestLine.hpp"
#include "RequestHeaders.hpp"
#include "../parse/Parser.hpp"
#include "../../exception/IllegalStateException.hpp"
#include "../SHTTP.hpp"

class RequestHeaders;

/**
 * @brief HTTP 요청 메시지 각 부분을 파싱하는 Derived class
 * @details request line, headers를 의미에 따라 파싱
 * @author chanhyle
 * @date 2023.03.29
 */
class RequestParser : public Parser {
public:
	static RequestLine		parseRequestLine(std::string __requestLineString);
	static RequestHeaders	parseHeaders(std::string __headersString);
	static std::string		parseBody(std::string __bodyString);
};

#endif