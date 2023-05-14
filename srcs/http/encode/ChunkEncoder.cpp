#include "ChunkEncoder.hpp"
#include "../SHTTP.hpp"
#include "../../util/Base.hpp"

const std::string ChunkEncoder::ZERO = "0" + SHTTP::CRLF + SHTTP::CRLF;

ChunkEncoder::ChunkEncoder(void) {}

ChunkEncoder::~ChunkEncoder(void) {}

std::string ChunkEncoder::encode(const std::string& input) {
	if (input.empty())
		return (ZERO);
	return (staticEncode(input) + ZERO);
}

std::string ChunkEncoder::staticEncode(const std::string& input) {
	std::string str = Base::toString<int>(input.size(), 16);
	return (str + SHTTP::CRLF + input + SHTTP::CRLF);
}
