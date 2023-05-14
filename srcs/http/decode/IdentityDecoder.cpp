#include "IdentityDecoder.hpp"
#include <iostream>
#include <string>

IdentityDecoder::IdentityDecoder(bool isAllocated, long long contentLength) :
		m_isAllocated(isAllocated),
		m_contentLength(contentLength),
		m_consumed() {}

IdentityDecoder::~IdentityDecoder(void) {}

bool IdentityDecoder::consume(const std::string &in, std::string &out, size_t &consumed, bool max) {
	consumed = std::min(in.size(), size_t(m_contentLength - m_consumed));

	if (!max)
		out.append(in.c_str(), in.c_str() + consumed);

	m_consumed += consumed;

	return (m_consumed == m_contentLength);
}

void IdentityDecoder::cleanup() {
	if (m_isAllocated)
		delete this;
}
