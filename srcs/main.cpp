#include "main.hpp"

#include <iostream>
#include "log/LogFactory.hpp"
#include "exception/Exception.hpp"
#include "exception/IOException.hpp"
#include "util/SEnvironment.hpp"
#include "util/ReleaseResource.hpp"
#include "http/Webserv.hpp"
#include "config/Config.hpp"
#include <signal.h>
#include <iostream>
#include <map>
#include <vector>


/*
/*
socket nonblock
https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking 
listen, accept 설명
https://blog.devkcr.org/172
https://helloworld-88.tistory.com/215
accept 두번째 인자로 client의 ip, port 정보를 받을 수 있나 ?
*/

//#include "iom/KqueueManage.hpp"
//	configuration file

// #define CONFIG_FILE "webserv.conf"


static bool gracefulShutdown = false;
Logger logger = LogFactory::get("main");
static Webserv *webserv = NULL;

void sighandler_term(int sig) {
	if (webserv) {
		gracefulShutdown = true;
		::signal(sig, SIG_DFL);
		logger.error("Graceful shutdown ...");
		webserv->stop();
	}
}

int main(int argc, char* argv[], char** envp) {

	signal(SIGPIPE, SIG_IGN);
	::signal(SIGINT, &sighandler_term);

	try {
		Config::instance();
		SEnvironment::setEnv(envp);
		webserv = Webserv::create();
		webserv->run();
		if (gracefulShutdown)
			logger.error("completed Shutdown!");
	} catch (IOException& e) {
		ReleaseResource::pointer<Webserv>(webserv);
		logger.error(e.message());
	}
	ReleaseResource::pointer<Webserv>(webserv);
	// system("leaks webserv");
	return (0);
}