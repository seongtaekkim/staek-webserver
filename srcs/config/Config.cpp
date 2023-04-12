#include "Config.hpp"

void test(std::string str) {
	std::cout << "test" << std::endl;
}

Config::Config(void) {
	std::cout << "constructor config" << std::endl;
	std::string r = Reader::from("../../config/default_webserv.conf").read();
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
	RootBlock root;
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
		root.check(key, value);
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
			std::list<ServerBlock*> list =  root.ServerBlockList();
			ServerBlock *serverBlock = new ServerBlock();
			ret = dest.find_first_of("{", ret);
			if (ret == std::string::npos) break;
			firstWord = dest.find_first_of("}", ret);
			if (firstWord == std::string::npos) break;
			ret++;
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
				std::string value = dest.substr(firstWord, ret - firstWord);
				serverBlock->check(key, value);
				ret++;
			}
			std::cout << serverBlock->getListen() << std::endl;
			root.appendServerBlock(serverBlock);
		}
	}
		std::cout << "result : " << root.getWorkerCnt() << std::endl;
		std::cout << "connection : " << root.getMaxConnection() << std::endl;
		std::cout << "listen : " << root.ServerBlockList().front()->getListen() << std::endl;
		std::cout << "servername : " << root.ServerBlockList().front()->getServerName() << std::endl;
		std::cout << "root : " << root.ServerBlockList().front()->getRoot() << std::endl;
		std::cout << "cgi : " << root.ServerBlockList().front()->getCgi().first << " " << root.ServerBlockList().front()->getCgi().second<< std::endl;


	std::string tmp = "../../config/mime.types";
	Mime *mime = new Mime(tmp);
	RootBlock *rootBlock = new RootBlock();
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