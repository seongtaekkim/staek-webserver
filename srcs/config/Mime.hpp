#ifndef MIME_HPP
#define MIME_HPP

#include <iostream>
#include <string>
#include <list>
#include <map>
#include "Reader.hpp"

// { type : extension1, extension2 .. }
class Mime {
public:
	typedef std::map<std::string, std::list<std::string> >	MimeMapType;
	typedef std::list<std::string>							MimeType;
private:
	MimeMapType _mimeMap;
	MimeType _mime;
	Mime(const Mime& other);
	Mime& operator=(const Mime& other);
public:
	Mime(void);
	Mime(const std::string file);
	~Mime(void);
	Mime::MimeMapType mimeMap(void) const;
	Mime::MimeType mime(void) const;
	std::string findType(std::string extension) const;
};

#endif