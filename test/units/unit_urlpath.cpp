#include "../../srcs/http/parse/PathParser.hpp"
#include "../test_unit.hpp"
#include <string>

static std::string parse(const char *str) {
	PathParser parser;

	while (*str)
		parser.parse(*str++);

	return (parser.path());
}

CASE("http-parser-path", "normal")
{
	ASSERT(parse("") == "/");
	ASSERT(parse("hello") == "/hello");
	ASSERT(parse("hello/world") == "/hello/world");

	return (0);
}

CASE("http-parser-path", "simple-decode")
{
	ASSERT(parse("hello%20world") == "/hello world");
	ASSERT(parse("hello%2520world") == "/hello%20world");

	return (0);
}
