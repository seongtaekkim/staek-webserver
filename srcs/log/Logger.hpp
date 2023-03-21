
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


/*
ref
time format : https://modoocode.com/122
ANSI color code : https://wiki.ubuntu-kr.org/index.php/ANSI_%EC%BB%AC%EB%9F%AC_%EC%BD%94%EB%93%9C
*/
class Logger {
private:
	time_t				_time;
	struct tm			*time_info;
	struct timeval		time_val;
	char 				time_buf[40];
	std::string			m_tag;

	Logger(const Logger* l);
	Logger& operator=(const Logger& l);
	void log(const std::string& color, std::string msg);
public: 
	Logger(void);
	Logger(const std::string &tag);
	~Logger(void);

	void	error(const std::string msg);
	void	warning(const std::string msg);
	void	info(const std::string msg);
	void	debug(const std::string msg);

	bool	isErrorEnabled() const;
};

#endif