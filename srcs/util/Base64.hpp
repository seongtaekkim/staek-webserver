#ifndef BASE64_HPP
#define BASE64_HPP

#include <cctype>
#include <string>
#include <stddef.h>

/**
 * @author https://stackoverflow.com/a/180949/7292958
 * @test   https://www.convertstring.com/ko/EncodeDecode/Base64Encode
 */
class Base64 {
public:
	static const std::string CHARACTERS;
private:
	Base64(void);
	Base64(const Base64& other);
	Base64& operator=(const Base64 &other);
public:
	~Base64(void);
	static std::string encode(const std::string& input);
	static std::string decode(const std::string& input);
	static bool isBase64(unsigned char c);
};

#endif
