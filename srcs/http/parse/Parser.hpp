#ifndef PARSER_HPP
#define PARSER_HPP

#include "PathParser.hpp"
#include "../../exception/Exception.hpp"
#include <vector>
#include <string>

// #define SP		' '
// #define CRLF	"\r\n"
#define HTAB	'\t'

/**
 * @brief Parser Base class
 * @details 파싱에서 공통적으로 사용될 함수들 정의
 * @author chanhyle
 * @date 2023.03.29
 */
class Parser {
public:
	enum STATE  {
		NOT_STARTED = 0,
		METHOD,
		SPACES_BEFORE_PATH,
		PATH,
		HTTP_START,
		HTTP_H,
		HTTP_HT,
		HTTP_HTT,
		HTTP_HTTP,
		HTTP_SLASH,
		HTTP_MAJOR,
		HTTP_DOT,
		HTTP_MINOR,
		HTTP_END_R,
		HTTP_END_N,
		HEADER_FIELDS,
		BODY,
		BODY_DECODE,
		END_R,
		END
	};
private:
	Parser::STATE	_state;
	PathParser		_pathParser;
	std::string		_method;
public:
	Parser(void);
	~Parser(void);
	static std::vector<std::string>		split(std::string str, std::string delim);
	static std::vector<std::string>		split(std::string str, char delim);
	static void							trim(std::string& str);
	static std::string					toupper(std::string str);

	void parse(char c);
	PathParser pathParser(void) const;
	std::string method(void);
	Parser::STATE state(void) const;
};

#endif