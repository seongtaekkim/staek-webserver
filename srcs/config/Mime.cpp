#include "Mime.hpp"


Mime::Mime(void) {}
Mime::Mime(const std::string file) {

	Reader r = Reader::from(file);

	std::size_t pos = 0;
	std::size_t ret = 0;

	std::string dest = r.read();
	ret = dest.find("types", pos);
	pos = ret;
	pos += 5;
	ret = dest.find("{", pos);
	pos = ret;
	pos += 1;
	    
	std::size_t endline = 0;
	std::string type ;
	std::list<std::string> extensions;
	std::size_t firstWord = 0;

	while (true) {
		endline = dest.find_first_of(SEMICOLON, pos);
		if (endline == std::string::npos)
			break ;

		// type search
		firstWord = dest.find_first_not_of(ISSPACE, pos);
		if (firstWord == std::string::npos) break;
		ret = dest.find_first_of(ISSPACE, firstWord);
		if (ret == std::string::npos) break;
		type = dest.substr(firstWord, ret - firstWord);

		// extension search
		while (true) {
			firstWord = dest.find_first_not_of(ISSPACE, ret);
			if (firstWord == std::string::npos) break;
			ret = dest.find_first_of(ISSPACE, firstWord);
			if (ret == std::string::npos) break;
			if (dest.c_str()[ret - 1] == ';') {
				extensions.push_back(dest.substr(firstWord, ret - firstWord - 1));
				break;
			}
			extensions.push_back(dest.substr(firstWord, ret - firstWord));
		}
		pos = ret;

		// type이 존재하면 list를 append 한다.
		if (_mimeMap[type].empty())
			_mimeMap[type] = extensions;
		else {
			for (std::list<std::string>::iterator l = extensions.begin() ; l != extensions.end() ; ++l) {
				_mimeMap[type].push_back(*l);
			}
		}
		extensions.clear();
	}
}

Mime::Mime(const Mime& other) {}

Mime& Mime::operator=(const Mime& other) {
	return (*this);
}

Mime::~Mime(void) {}

Mime::MimeMapType Mime::mimeMap(void) const {
	return (this->_mimeMap);
}

Mime::MimeType Mime::mime(void) const {
	return (this->_mime);
}
