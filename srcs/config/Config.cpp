#include "Config.hpp"

class RootBlock;

Config::Config(void) {
	std::string r = Reader::from(CONFIG_FILE).read();
	std::size_t ret = 0;

	std::string dest = r;
	    
	std::string type ;
	std::list<std::string> extensions;
	std::size_t firstWord = 0;

	RootBlock *rootBlock = new RootBlock();
	
	while (true) {
		firstWord = dest.find_first_not_of(ISSPACE, ret);
		if (firstWord == std::string::npos) break;
		ret = dest.find_first_of(ISSPACE, firstWord);
		if (ret == std::string::npos) break;
		std::string key =  dest.substr(firstWord, ret - firstWord);
		
		firstWord = dest.find_first_not_of(ISSPACE, ret);
		if (firstWord == std::string::npos) break;
		ret = dest.find_first_of(SEMICOLON, firstWord);
		if (ret == std::string::npos) break;
		std::string value =  dest.substr(firstWord, ret - firstWord);
		rootBlock->check(key, value);
		ret++;
	}
	ret = 0;
	firstWord = 0;
	while (true) {
		firstWord = dest.find_first_not_of(ISSPACE, ret);
		if (firstWord == std::string::npos) break;
		ret = dest.find_first_of(ISSPACE, firstWord);
		if (ret == std::string::npos) break;
		if (dest.substr(firstWord, ret - firstWord).compare("server") == 0) {
			ServerBlock *serverBlock = new ServerBlock();
			ret = dest.find_first_of("{", ret);
			if (ret == std::string::npos) break;
			firstWord = dest.find_first_of("}", ret);
			if (firstWord == std::string::npos) break;
			ret++;
			while (true) {

				firstWord = dest.find_first_not_of(ISSPACE, ret);
				if (firstWord == std::string::npos) break;
				ret = dest.find_first_of(ISSPACE, firstWord);
				if (ret == std::string::npos) break;
				std::string key =  dest.substr(firstWord, ret - firstWord);
				if (key.compare("}") == 0)
					break;
				if (dest.substr(firstWord, ret - firstWord).compare("location") == 0) {
					LocationBlock *locationBlock = new LocationBlock();
					firstWord = dest.find_first_not_of(ISSPACE, ret);
					if (firstWord == std::string::npos) break;
					ret = dest.find_first_of(ISSPACE, firstWord);
					if (ret == std::string::npos) break;
					locationBlock->check("path", dest.substr(firstWord, ret - firstWord));
					ret = dest.find_first_of("{", ret);
					if (ret == std::string::npos) break;
					firstWord = dest.find_first_of("}", ret);
					if (firstWord == std::string::npos) break;
					ret++;
					
					while (true) {
						firstWord = dest.find_first_not_of(ISSPACE, ret);
						if (dest.at(firstWord) == '}') { ret = firstWord; ret++; break;}
						if (firstWord == std::string::npos) break;
						ret = dest.find_first_of(ISSPACE, firstWord);
						if (ret == std::string::npos) break;
						std::string key =  dest.substr(firstWord, ret - firstWord);
						
						firstWord = dest.find_first_not_of(ISSPACE, ret);
						if (firstWord == std::string::npos) break;
						ret = dest.find_first_of(SEMICOLON, firstWord);
						if (ret == std::string::npos) break;
						std::string value = dest.substr(firstWord, ret - firstWord);
						locationBlock->check(key, value);
						ret++;
					}
					serverBlock->appendLocationBlock(locationBlock);
					continue;
				}

				firstWord = dest.find_first_not_of(ISSPACE, ret);
				if (firstWord == std::string::npos) break;
				ret = dest.find_first_of(SEMICOLON, firstWord);
				if (ret == std::string::npos) break;
				std::string value = dest.substr(firstWord, ret - firstWord);
				serverBlock->check(key, value);
				ret++;
			}
			rootBlock->appendServerBlock(serverBlock);
		}
	}

	std::string tmp = rootBlock->getInclude();
	Mime *mime = new Mime(tmp);
	this->_file = CONFIG_FILE;
	this->_mime = mime;
	this->_root = rootBlock;
}

Config::~Config(void) {
	ReleaseResource::pointer<Mime>(this->_mime);
}

const Mime* Config::mime(void) {
	return (this->_mime);
}

RootBlock* Config::rootBlock(void) {
	return (this->_root);
}
