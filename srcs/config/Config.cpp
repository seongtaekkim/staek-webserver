#include "Config.hpp"

class RootBlock;

Config::Config(void) {
	std::cout << "constructor config" << std::endl;
	std::string r = Reader::from(CONFIG_FILE).read();
	// std::cout << r << std::endl;
	/*
	root 내용
	mimie내용
	servers 내용
	locations 내용
	*/
	std::size_t pos = 0;
	std::size_t ret = 0;

	std::string dest = r;
	    
	std::size_t endline = 0;
	std::string type ;
	std::list<std::string> extensions;
	std::size_t firstWord = 0;

	/*
	1. 내가 정의한 키만 함수포인터를 만들고 find로 체크 된 부분만 세팅함 : 내가정의한게 아닌건 어차피 의미가 없다.
	- include :
	2. vlidate 돌린다.
	*/
	/*
	root 객체생성
	파일을 읽으면서 키값이 이미 생성된 맵 정보에 있는 지 확인
	있다면 함수실행
	server블록을 읽었다면 
	*/

	RootBlock *rootBlock = new RootBlock();
	// std::map<std::string, void(*)(std::string)> _map;
	// _map["worker_connections"] = test;
	// _map["waf"]("weaf");
	
	// root block
	while (true) {
		//std::cout << dest << std::endl;
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
	// server blocks
	while (true) {
		//std::cout << dest << std::endl;
		firstWord = dest.find_first_not_of(ISSPACE, ret);
		if (firstWord == std::string::npos) break;
		ret = dest.find_first_of(ISSPACE, firstWord);
		if (ret == std::string::npos) break;
	
		// 여러개일 수 있지만 우선 한개
		if (dest.substr(firstWord, ret - firstWord).compare("server") == 0) {
			// std::list<ServerBlock*> list =  root.ServerBlockList();
			ServerBlock *serverBlock = new ServerBlock();
			ret = dest.find_first_of("{", ret);
			if (ret == std::string::npos) break;
			firstWord = dest.find_first_of("}", ret);
			if (firstWord == std::string::npos) break;
			ret++;
			while (true) {
				// if (dest.at(ret) == '}') break;

				firstWord = dest.find_first_not_of(ISSPACE, ret);
				if (firstWord == std::string::npos) break;
				ret = dest.find_first_of(ISSPACE, firstWord);
				if (ret == std::string::npos) break;
				std::string key =  dest.substr(firstWord, ret - firstWord);
				// std::cout << "===========server key : " << key << std::endl;
				if (dest.substr(firstWord, ret - firstWord).compare("location") == 0) {
					// std::cout << "location start : " << std::endl;
					// std::list<LocationBlock*> list =  serverBlock->LocationBlockList();
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
			std::cout << serverBlock->getListen() << std::endl;
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
	// server, loaction block release
}

const Mime* Config::mime(void) {
	return (this->_mime);
}

RootBlock* Config::rootBlock(void) {
	return (this->_root);
}
