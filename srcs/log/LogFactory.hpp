#ifndef LOGFACTORY_HPP
#define LOGFACTORY_HPP


#include "Logger.hpp"
#include <map>
#include <string>

/**
 * @brief log 컨테이너를 관리하는 객체이다.
 * @details 클래스별 로그배열을 관리한다.
 * @author seongtki
 * @date 2023.03.21
 */
class LogFactory {
public:
	typedef std::map<std::string, Logger*>	logger_map;
	typedef logger_map::iterator			iterator;

private:
	static logger_map &getStorage();

public:
	static Logger& get(const std::string &tag);
	static void destroy(void);
};

#endif