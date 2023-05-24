#include "IdentityDecoder.hpp"
#include <iostream>
#include <string>

IdentityDecoder::IdentityDecoder(bool isAllocated, long long contentLength) :
		_isAllocated(isAllocated),
		_contentLength(contentLength),
		_consumed() {}

IdentityDecoder::~IdentityDecoder(void) {}

bool IdentityDecoder::parse(const std::string &in, std::string &out, size_t &consumed, bool max) {
	consumed = std::min(in.size(), size_t(_contentLength - _consumed));

	if (!max)
		out.append(in.c_str(), in.c_str() + consumed);

	_consumed += consumed;
	if (_consumed == _contentLength)
		return (true);
	return (false);
}

void IdentityDecoder::cleanup() {
	if (_isAllocated)
		delete this;
}
