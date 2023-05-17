#include "Base.hpp"
#include <stdlib.h>

const std::string Base::DECIMAL = "0123456789";
const std::string Base::HEX = "0123456789abcdef";

Base::Base(void) {}

Base::~Base(void) {}

int	Base::getBase(char c, std::string base) {
	int index = base.find(c);
	if (index == std::string::npos)
		return (-1);
	return (index);
}

std::string Base::toUpper(const std::string& base) {
	std::string				out;
	const char* 			arr = base.c_str();
	std::string::size_type	size = base.size();

	while (*arr) {
		out += std::toupper(*arr);
		arr++;
	}
	return (out);
}
