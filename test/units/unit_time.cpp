#include "../test_unit.hpp"
#include <unistd.h>
#include <iostream>
#include "../../srcs/http/SHTTP.hpp"
#include "../../srcs/util/Time.hpp"

CASE("time==================", "test1")
{	
	Time t;
	ASSERT(t.format(SHTTP::DATEFORMAT) == "Thu, 01 Jan 1970 09:00:00 GMT");
	return (0);
}
