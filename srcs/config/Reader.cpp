#include "Reader.hpp"
#include "../exception/IOException.hpp"
#include <sys/errno.h>
#include <fstream>
#include <sstream>

Reader::Reader() : _parser("")
{
}

Reader::Reader(const std::string &source) : _parser(source)
{
}

Reader::Reader(const Reader &other) : _parser(other._parser)
{
}

Reader::~Reader() {}

Reader& Reader::operator=(const Reader &other) {
	if (this != &other) {
		// m_parser = other.m_parser;
	}
	return (*this);
}

std::string Reader::read(void) {
	return this->_parser;
}
// Reader*
// Reader::read(void)
// {

// 	if (m_parser.hasNext())
// 	{
// 		JsonValue *value = NULL;

// 		try
// 		{
// 			m_parser.next();

// 			value = m_parser.get();

// 			m_parser.hasNext();

// 			return (value);
// 		}
// 		catch (...)
// 		{
// 			if (value)
// 				delete value;

// 			throw;
// 		}
// 	}

// 	//throw internalException();
// }

Reader Reader::from(const std::string &path) {
	std::ifstream filestream(path.c_str());
	if (!filestream.is_open())
		throw IOException("Failed to open: " + path, errno);

	std::stringstream buffer;
	buffer << filestream.rdbuf();

	return (Reader(buffer.str()));
}
