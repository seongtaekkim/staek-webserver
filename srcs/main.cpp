
#include <iostream>
#include "log/LogFactory.hpp"


Logger log = LogFactory::get("main");
int main(int argc, char* argv[]) {
	if (argc != 2) {
		log.error("please input argument only one");
	}
	
	//config file 파싱 
	//parse(argv[1]);

	// server 객체생성
	// socket 정보생성 -> listen 시작


	// client 에서 요청
	// server의 소켓에서 요청을 받고 작업큐에 삽입
	// request 에서 요청헤더 해석
	// response 에서 응답헤더 생성, send()
	// -> method 로직 
	// -> cgi 로직
	return (0);
}