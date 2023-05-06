#include "../../srcs/http/Header.hpp"
#include "../../srcs/http/parse/Parser.hpp"
#include "../test_unit.hpp"

static Header
parse(const char *str)
{
	Parser parser;

	while (*str)
		parser.headerParse(*str++);

	return (parser.header());
}

CASE("http-parser-headerfields", "normal")
{
	ASSERT(parse("") == Header());
	ASSERT(parse("Hello: World\r\n") == Header().set("Hello", "World"));
	ASSERT(parse("Hello: World\r\nFrom: Unit-Testing\r\n") == Header().set("Hello", "World").set("From", "Unit-Testing"));

	return (0);
}
