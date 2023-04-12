#ifndef MIME_HPP
#define MIME_HPP

#include <iostream>
#include <string>
#include <list>
#include <map>
#include "Reader.hpp"

//http://egloos.zum.com/hanulnun/v/2694379
// { type : extension1, extension2 .. }
class Mime {
public:
	typedef std::map<std::string, std::list<std::string> > MimeType;
private:
	MimeType _mimeMap;
public:
	Mime(void);
	Mime(const Mime& other);
	Mime& operator=(const Mime& other);
	Mime(const std::string file);
	~Mime(void);
	Mime::MimeType mime(void) const;
};

#endif