#include "../../exception/Exception.hpp"
#include "ChunkDecoder.hpp"
#include <cstdlib>
#include <iostream>

ChunkDecoder::ChunkDecoder(bool isAllocated) :
		_isAllocated(isAllocated),
		_state(NOT_STARTED),
		_sizeNb(0),
		_sizeStr(""),
		_parsedChunk(""),
		_totalSize(0) {}

ChunkDecoder::~ChunkDecoder() {}

bool ChunkDecoder::parse(const std::string& in, std::string& out, size_t &consumed, bool max) {
	std::string copy = in;
	
	if (in.empty())
		return (false);
	while (1)
	{
		switch (_state)
		{
			case NOT_STARTED:
			case SIZE:
			{
				size_t found;
				found = copy.find("\r\n");
				
				if (found != std::string::npos)
				{
					if (found != 0)
						_sizeStr = copy.substr(0, found);
					else
						_sizeStr = copy.substr(0, 1);
					
					consumed += found + 2;
			
					if (_sizeStr.empty())
					{
						_state = SIZE;
						return (false);
					}
					
					char *endPtr;		
					std::string hex_intro = "0x" + _sizeStr;			
					_sizeNb = ::strtol(hex_intro.c_str(), &endPtr, 16);	
					if (endPtr == hex_intro.c_str())						
						throw Exception ("Hexadecimal conversion impossible"); 
					_sizeStr = "";
					copy.erase(0, found + 2);
				}
				else
				{
					return (false);
				}

				if (_sizeNb == 0)
				{
					_state = OVER;
					return (true);
				
				}
				else
				{
					_state = CHUNK;	
				}
				break;
			}

			case CHUNK:
			{
				if (copy.size() <= (size_t)_sizeNb)
				{
			
					out += copy;
					_sizeNb -= copy.size();
					consumed += copy.size();
					copy.erase(0, std::string::npos);
				}
				else
				{
					_parsedChunk = copy.substr(0, _sizeNb);
					if (!max)
						out += _parsedChunk;
					consumed += _sizeNb;
					_parsedChunk = "";
					
					copy.erase(0, _sizeNb);
					_sizeNb = 0;
				}
				
				if (_sizeNb == 0)
				{
					_state = CHUNK_END;
				}
				if (copy.empty())
					return (false);
				break;
			}

			case CHUNK_END:
			{
				size_t f;
				
				f = copy.find("\r\n");
				if (f != std::string::npos)
				{
					consumed += f + 2;
					copy.erase(0, f + 2);
					_state = SIZE;
				}
				else if ((f = copy.find("\r")) != std::string::npos)
				{
					consumed += f + 1;
					copy.erase(0, f + 1);
					_state = CHUNK_END2;
				}
				else
				{
					return (false);
				}
				if (copy.empty())
					return (false);

				break;
			}
			case CHUNK_END2:
			{
				std::size_t f;
				f = copy.find("\n");
				if (f != std::string::npos)
				{
					consumed += f + 1;
					copy.erase(0, f + 1);
					_state = SIZE;
				}
				else if (copy.size() != 0)
				{
					_state = CHUNK_END;
				}
				
				if (copy.empty())
					return (false);
					
				break;
			}	
			case OVER:
			{
				return (true);
			}
		}
	}
	return (false);
}

ChunkDecoder::State ChunkDecoder::state() {
	return (_state);
}

void ChunkDecoder::cleanup() {
	if (_isAllocated)
		delete this;
}
