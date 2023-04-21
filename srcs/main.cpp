
#include <iostream>
#include "log/LogFactory.hpp"
#include "exception/Exception.hpp"
#include "exception/IOException.hpp"
#include <iostream>
#include <map>
#include <vector>


using namespace std;

/*
socket nonblock
https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking 
listen, accept 설명
https://blog.devkcr.org/172
https://helloworld-88.tistory.com/215
accept 두번째 인자로 client의 ip, port 정보를 받을 수 있나 ?
*/

//#include "iom/KqueueManage.hpp"
#include "http/Webserv.hpp"
#include "config/Config.hpp"
#include <signal.h>
/*
	configuration file
*/
// #define CONFIG_FILE "webserv.conf"


static bool gracefulShutdown = false;
Logger logger = LogFactory::get("main");

void
sighandler_term(int sig)
{
	// if (httpOrchestrator)
	// {
		gracefulShutdown = true;
		::signal(sig, SIG_DFL);
		logger.error("Graceful shutdown asked... (do CTRL-C again to quit immediately)");
		// httpOrchestrator->stop();
	// }
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		logger.error("please input argument only one ?인자를 꼭 넣어야하나 안넣고 걍할까 그게낫지않나");
	}
	signal(SIGPIPE, SIG_IGN);

	// if (!ignoreGracefulStop)
		// {
		::signal(SIGINT, &sighandler_term);
			// LOG.debug() << "Installed signal handler: " << (void*)&sighandler_term << std::endl;
		// }
	// kqueueEx();
	try {
		Config::instance();
		Webserv::start();
	} catch (IOException& e) {
		logger.error(e.message());
	}

	// server 객체생성
	// socket 정보생성 -> listen 시작

	// client 에서 요청
	// server의 소켓에서 요청을 받고 작업큐에 삽입
	// request 에서 요청헤더 해석
	// response 에서 응답헤더 생성, send()
	// -> method 로직 
	// -> cgi 로직


	// socket
	/*
	socket 객체
	소켓관리
	socket
	bind
	listen
	accept 관리
	- 새로 생성, 유지, 종료 주기를 정해야 한다.
	*/
	return (0);
}