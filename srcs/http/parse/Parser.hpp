#ifndef PARSER_HPP
#define PARSER_HPP

#include "PathParser.hpp"
#include "../../exception/Exception.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "../Header.hpp"
#include "../encode/HTTPBodyEncoding.hpp"
#include "../decode/IHTTPBodyDecoder.hpp"
#define HTAB	'\t'

class Header;
class Client;
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
	int				_state;
	PathParser		_pathParser;
	std::string		_method;

	int				_hState;
	long			_headerSize;
	Header			_header;
	std::string		m_key;
	std::string		m_value;
	IHTTPBodyDecoder* _bodyDecoder;
	Client&			_client;
	bool _isMax;
	int				_major;
	int				_minor;
	unsigned long	_clientMaxBodySize;
	Parser(void);
public:
	Parser(Client& client);
	~Parser(void);

	void parse(char c);
	PathParser pathParser(void) const;
	std::string method(void);
	int			state(void);
	void state(int state);

	void headerParse(char c);
	void commit(Parser::HSTATE nextState);
	void headerClear(void);
	int hState(void) const;
	void hState(int state);

	const Header& header(void) const;

	unsigned long clientMaxBodySize(void) const;
	void clientMaxBodySize(unsigned long size);

};

#endif