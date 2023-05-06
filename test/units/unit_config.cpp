/*
	findMimeType
	findMimeExtension 만들어야함.

	메모리릭 테스트 필요함

	} <= 이거 안찾음

	예외처리 테스트 필요
	불필요 헤더 점검 필요
	코드 리펙토링 필요
	break 대신에 throw parseException 추가 필요
	자원해제 코드 추가 필요
	함수포인터 정의 위치 옮길 수 있게 코드 개선 필요
*/

#include "../test_unit.hpp"
#include <iostream>
#include "../../srcs/config/Reader.hpp"
#include "../../srcs/config/Mime.hpp"
#include <map>
#include <list>
#include "../../srcs/config/Config.hpp"


/*
Config.hpp > CONFIG_FILE 변경
*/
CASE("config", "mime, block list")
{
	Config::instance();
	Config::instance().mime();
	// Mime::MimeType mimeMap =  Config::instance().mime()->mime();
	// int cnt = 1;
	// for (Mime::MimeType::iterator i =  mimeMap.begin() ; i != mimeMap.end() ; i++) {
	// 	std::cout << cnt << " " << (*i) << " : ";
	// 	for (std::list<std::string>::iterator j = (*i).second.begin() ; j != (*i).second.end() ; j++) {
	// 		std::cout << *j << " ";
	// 	}
	// 	std::cout << std::endl;
	// 	cnt++;
	// }
	// RootBlock *root = Config::instance().rootBlock();
	// std::cout << "result : " << root->getWorkerCnt() << std::endl;
	// std::cout << "connection : " << root->getMaxConnection() << std::endl;
	// std::cout << "include : " << root->getInclude() << std::endl;
	// std::cout << "listen : " << root->ServerBlockList().front()->getListen() << std::endl;
	// std::cout << "servername : " << root->ServerBlockList().front()->getServerName() << std::endl;
	// std::cout << "root : " << root->ServerBlockList().front()->getRoot() << std::endl;
	// std::cout << "cgi : " << root->ServerBlockList().front()->getCgi().first << " " << root->ServerBlockList().front()->getCgi().second<< std::endl;
	
	// std::cout << "location size : " << root->ServerBlockList().front()->LocationBlockList().size() << std::endl;

	// std::list<LocationBlock *> list = root->ServerBlockList().front()->LocationBlockList();
	// for (std::list<LocationBlock *>::iterator i = list.begin()
	// 		; i !=list.end() ; ++i) {
	// 	std::cout << "index : " << (*i)->getIndex()<< std::endl;
	// 	std::cout << "path : " << (*i)->getPath() << std::endl;
	// }
	// ASSERT(1==1);
	return (0);
}