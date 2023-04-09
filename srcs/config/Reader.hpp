#ifndef READER_HPP
#define READER_HPP

#include <string>
// #include "../exception/IllegalStateException.hpp"
// #include "../exception/IOException.hpp"

class Reader {
	private:
		std::string _parser;

	public:
		Reader(void);
		Reader(const std::string& source);
		Reader(const Reader& other);
		virtual ~Reader(void);

		Reader& operator=(const Reader &other);

	public:
		// JsonValue*
		std::string
		read(void);

		// JsonStructure*
		// readStructure(void);

		// JsonArray*
		// readArray(void);

		// JsonObject*
		// readObject(void);

	public:
		static Reader from(const std::string& path);
};

#endif
