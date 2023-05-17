#include "Replace.hpp"

Replace::Replace(void) {}
Replace::~Replace(void) {}

std::string Replace::replace(std::string s0, const std::string s1, const std::string s2) {
	std::size_t pos = 0;
	std::size_t ret = 0;

	if (s0.size() == 0 || s1.size() == 0) {
		return (std::string());
	}
	while(true) {
		ret = s0.find(s1, pos);
		if(ret == std::string::npos) {
			break ;
		}
		else {
			pos = ret;
			s0.erase(pos, s1.size());
			s0.insert(pos, s2);
			pos += s2.size();
		}
	}
	return (s0);
}