
#include "LogFactory.hpp"
#include "Logger.hpp"

/**
* @brief 요청인자에 해당하는 로그 컨테이너를 리턴한다.
		컨테이너에 없다면, 생성 후 리턴한다.
* @return Logger 
* @param 로그 이름
* @date 2023.03.21
*/
Logger&
LogFactory::get(const std::string &tag)
{
	logger_map &storage = getStorage();

	iterator it = storage.find(tag);
	if (it == storage.end())
		it = storage.insert(storage.end(), std::pair<std::string, Logger*>(tag, new Logger(tag)));
	return (*it->second);
}

/**
* @brief 로그 컨테이너 자원해제
* @date 2023.03.21
*/
void
LogFactory::destroy(void)
{
	logger_map &storage = getStorage();

	for (iterator it = storage.begin(); it != storage.end(); it++)
		delete it->second;
	storage.clear();
}

/**
* @brief 정적 로그map 을 생성한다.
* @return LogFactory::logger_map&
* @param 로그 이름
* @date 2023.03.21
*/
LogFactory::logger_map&
LogFactory::getStorage()
{
	static logger_map storage;
	return (storage);
}
