#ifndef PARSER_HPP
#define PARSER_HPP

#include "PathParser.hpp"
#include "../../exception/Exception.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "../Header.hpp"

#define HTAB	'\t'

class Header;

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
	enum HSTATE
	{
		FIELD = 20,
		COLON,
		SPACES_BEFORE_VALUE,
		VALUE,
		SPACES_AFTER_VALUE,
		HEND_R,
		HEND_N,
		HEND_R2,
		HEND
	};
	static long headerMaxLength;
private:
	Parser::STATE	_state;
	PathParser		_pathParser;
	std::string		_method;

	Parser::HSTATE	_hState;
	long			_headerSize;
	Header			_header;
	std::string		m_key;
	std::string		m_value;
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
	Parser::STATE state(void);
	void state(Parser::STATE state);

	void headerParse(char c);
	void commit(Parser::HSTATE nextState);
	void headerClear(void);
	Parser::HSTATE hState(void) const;

	const Header& header(void) const;

};

#endif