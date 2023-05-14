#ifndef CHUNKENCODER_HPP
#define CHUNKENCODER_HPP

#include "IHTTPBodyEncoder.hpp"
#include <string>

class ChunkEncoder : public IHTTPBodyEncoder {
public:
	static const std::string ZERO;

private:
	ChunkEncoder(const ChunkEncoder &other);
	ChunkEncoder& operator=(const ChunkEncoder &other);

public:
	ChunkEncoder(void);
	virtual ~ChunkEncoder(void);
	std::string encode(const std::string &input);

public:
	static std::string
	staticEncode(const std::string &input);
};

#endif
