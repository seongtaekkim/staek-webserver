#include "../../srcs/log/LogFactory.hpp"
#include "../test_unit.hpp"

Logger log = LogFactory::get("test");

CASE("log", "loglevel")
{
	
	// ASSERT(log.isErrorEnabled() == ERROR);
	return (0);
}


// #include "test.hpp"


// void logTest(void) {
	// std::cout << std::endl;
	// log.error("error log test1");
	// log.error("error log test2");
	//log.debug("");
	// TEST_MSG("log level");
// }
// 
// TEST_LIST = {
// 	{"log test", logTest},
// 	{0}
// };