#ifndef PARSER_HPP
#define PARSER_HPP
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
public :
	static std::vector<std::string>		split(std::string str, std::string delim);
	static std::vector<std::string>		split(std::string str, char delim);
	static void							trim(std::string& str);
	static std::string					toupper(std::string str);
};

#endif