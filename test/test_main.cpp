
#include "../srcs/exception/Exception.hpp"
#include "case/TestCase.hpp"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::list<TestCase> > g_test_units_and_cases;

int
main(int argc, char **argv, char **envp)
{
	const char *program = argv[0];

	bool doContinue = false;

	std::cout << "Starting test units" << std::endl;

	for (std::map<std::string, std::list<TestCase> >::iterator it = g_test_units_and_cases.begin(); it != g_test_units_and_cases.end(); it++)
	{
		const std::string &unit = it->first;
		const std::list<TestCase> &cases = it->second;

		std::cout << std::endl;
		std::cout << "UNIT: " << unit << std::endl;

		int index = 0;
		for (std::list<TestCase>::const_iterator it2 = cases.begin(); it2 != cases.end(); it2++)
		{
			const TestCase &testCase = *it2;

			std::cout << "  CASE " << ++index << "/" << cases.size() << ": " << it2->name() << std::endl;

			if ((*(testCase.function()))(argc, argv, envp))
			{
				if (!doContinue)
					return (1);
			}
		}
	}

	return (0);
}
