
#include "Logger.hpp"
#include <map>
#include <string>

class LogFactory {
public:
	typedef std::map<std::string, Logger*> logger_map;
	typedef logger_map::iterator iterator;

private:
	static logger_map &getStorage();

public:
	static Logger&
	get(const std::string &tag);

	static void
	destroy(void);
};