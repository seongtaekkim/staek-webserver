#include "IHTTPBodyDecoder.hpp"
#include <iostream>

IHTTPBodyDecoder::~IHTTPBodyDecoder(void) {}

std::string IHTTPBodyDecoder::decode(const std::string &input, bool max) {
	std::string out;

	size_t consumed = 0;
	consume(input, out, consumed, max);

	return (out);
}

void IHTTPBodyDecoder::cleanup() {}
