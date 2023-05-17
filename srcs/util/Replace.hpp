#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <iostream>

class Replace {
public:
	Replace(void);
	~Replace(void);
	static std::string replace(std::string s0, const std::string s1, const std::string s2);
};

#endif