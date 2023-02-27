
#include "LogFactory.hpp"
#include "Logger.hpp"
#include <utility>

Logger&
LogFactory::get(const std::string &tag)
{
	logger_map &storage = getStorage();

	iterator it = storage.find(tag);
	if (it == storage.end())
		it = storage.insert(storage.end(), std::pair<std::string, Logger*>(tag, new Logger(tag)));
	return (*it->second);
}

void
LogFactory::destroy(void)
{
	logger_map &storage = getStorage();

	for (iterator it = storage.begin(); it != storage.end(); it++)
		delete it->second;
	storage.clear();
}

LogFactory::logger_map&
LogFactory::getStorage()
{
	static logger_map storage;

	return (storage);
}
