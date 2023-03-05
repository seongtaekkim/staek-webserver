#ifndef TEST_UNIT_HPP
# define TEST_UNIT_HPP

// #include "../srcs/log/LogFactory.hpp"
#include <iostream>

# ifndef RUN_TESTS
#  define RUN_TESTS 1
# endif

#include "case/TestCase.hpp"
#include <list>
#include <map>
#include <string>

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)

/* from: https://stackoverflow.com/a/1597129/7292958 */
# define TOKENPASTE(x, y) x ## y
# define TOKENPASTE2(x, y) TOKENPASTE(x, y)

# define CASE_OBJECT_NAME TOKENPASTE2(AUTO_DECLARED_CASE, __LINE__)
# define CASE_METHOD_NAME TOKENPASTE2(AUTO_DECLARED_METHOD, __LINE__)

# define FILE_LOCATION __FILE__ ":" TOSTRING(__LINE__)

# if RUN_TESTS
#  define CASE(unit, name) \
	static int CASE_METHOD_NAME(int argc, char **argv, char **envp); \
	static TestCase CASE_OBJECT_NAME(unit, name, FILE_LOCATION, &CASE_METHOD_NAME); \
	static int CASE_METHOD_NAME(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, __attribute__((unused)) char **envp)
# else
#  define CASE(unit, name) \
	static int __attribute__((unused)) CASE_METHOD_NAME(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, __attribute__((unused)) char **envp)
# endif

// static Logger TEST_CASE_LOG = LoggerFactory::get("test-case");

# define ASSERT(cond) \
	if (!(cond)) \
	{ \
		std::cerr << "ASSERT() " << __FILE__ << ":" << __LINE__ << " -- " << #cond << std::endl; \
		return (1); \
	}

# define ASSERT_EXCEPT(code) \
	try \
	{ \
		code; \
		std::cerr << "ASSERT_EXCEPT() " << __FILE__ << ":" << __LINE__ << " -- " << #code << std::endl; \
		return (1); \
	} \
	catch (...) \
	{ \
	}

# define ASSERT_NO_EXCEPT(code) \
	try \
	{ \
		code; \
	} \
	catch (std::exception &exception) \
	{ \
		std::cerr << "ASSERT_NO_EXCEPT() " << __FILE__ << ":" << __LINE__ << " -- " << #code << " -- " << exception.what() << std::endl;  \
		return (1); \
	}

extern std::map<std::string, std::list<TestCase> > g_test_units_and_cases;

int
test_main(int argc, char **argv, char **envp);

#endif
