#ifndef CHUNKDECODER_HPP
#define CHUNKDECODER_HPP

#include "IHTTPBodyDecoder.hpp"
#include <stddef.h>
#include <string>

class ChunkDecoder : public IHTTPBodyDecoder {
public:
	enum State {
		NOT_STARTED = 0,
		SIZE,
		CHUNK,
		CHUNK_END,
		CHUNK_END2,
		OVER
	};

private:
	bool _isAllocated;
	State _state;

private:
	ChunkDecoder();
	ChunkDecoder(const ChunkDecoder &other);
	ChunkDecoder& operator=(const ChunkDecoder &other);

public:
	ChunkDecoder(bool isAllocated);
	virtual ~ChunkDecoder();

	bool parse(const std::string &in, std::string &out, size_t &consumed, bool max);

	void cleanup();

	ChunkDecoder::State state();

	static inline bool isValidCharacter(char c) {
		return (std::isalnum(c));
	}

private:
	int _sizeNb;
	std::string _sizeStr;
	std::string _parsedChunk;
	long long _totalSize;
};

#endif
