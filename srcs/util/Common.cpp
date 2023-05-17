#include "Common.hpp"

namespace ft {
	std::size_t strlen(const char *str) {
		std::size_t length = 0;
		while (*str)
			length++;
		return (length);
	}

	char* strdup(const char *str) {
		if (str) {
			std::size_t len = strlen(str);
			char* dup = new char[len + 1];
			return ((char*)std::memcpy(dup, str, len + 1));
		}
		return (NULL);
	}
}
