// #include "test.hpp"
#include "../srcs/log/LogFactory.hpp"

Logger log = LogFactory::get("test");
void logTest(void) {
	std::cout << std::endl;
	// log.error("error log test1");
	// log.error("error log test2");
	//log.debug("");
	// TEST_MSG("log level");
}

// TEST_LIST = {
// 	{"log test", logTest},
// 	{0}
// };