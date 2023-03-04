#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "Server.hpp"

typedef std::set<int, int>			Fds;
typedef std::vector<Listen>					Listens;
typedef std::vector<std::string>			Methods;
typedef std::set<std::string, std::string>	ErrorPages;
typedef std::vector<std::string>			Tokens;

#endif
