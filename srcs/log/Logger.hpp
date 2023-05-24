
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

#define ORIGIN   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

#define DEBUG 1
#define WARNING 1
#define INFO 1
#define ERROR 1


/**
 * @brief level별로 log를 출력한다.
 * @details 시간 + 인자를 출력한다.
 * 			color : 시간(파란색)
 * 					인자(로그레벨 색상)
 * 					ERROR(red)
 * 					WARN()
 * 					INFO()
 * 					DEBUG()
 * @ref time format : https://modoocode.com/122
 *		ANSI color code : https://wiki.ubuntu-kr.org/index.php/ANSI_%EC%BB%AC%EB%9F%AC_%EC%BD%94%EB%93%9C
 * @author seongtki
 * @date 2023.03.21
 */
class Logger {
private:
	time_t				_time;
	struct tm			*time_info;
	struct timeval		time_val;
	char 				time_buf[40];
	std::string			m_tag;

	Logger(void);
	Logger(const Logger* l);
	Logger& operator=(const Logger& l);
	void log(const std::string& color, std::string msg);
public: 
	Logger(const std::string &tag);
	~Logger(void);

	void	error(const std::string msg);
	void	warning(const std::string msg);
	void	info(const std::string msg);
	void	debug(const std::string msg);

	bool	isErrorEnabled() const;
	bool	isWarnEnabled() const;
	bool	isInfoEnabled() const;
	bool	isDebugEnabled() const;
};

#endif