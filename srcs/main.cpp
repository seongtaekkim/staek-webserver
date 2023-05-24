#include "main.hpp"

#include <iostream>
#include "log/LogFactory.hpp"
#include "exception/Exception.hpp"
#include "exception/IOException.hpp"
#include "exception/RuntimeException.hpp"
#include "util/SEnvironment.hpp"
#include "util/ReleaseResource.hpp"
#include "http/Webserv.hpp"
#include "config/Config.hpp"
#include <signal.h>
#include <iostream>
#include <map>
#include <vector>


Logger logger = LogFactory::get("main");
static bool gracefulShutdown = false;
static Webserv *webserv = NULL;

void handler(int sig) {
	if (webserv) {
		gracefulShutdown = true;
		::signal(sig, SIG_DFL);
		logger.error("Graceful shutdown ...");
		webserv->stop();
	}
}

int main(int argc, char* argv[], char** envp) {

	(void)argc;
	(void)argv;

	signal(SIGPIPE, SIG_IGN);
	::signal(SIGINT, &handler);

	try {
		Config::instance();
		SEnvironment::setEnv(envp);
		webserv = Webserv::create();
		webserv->run();
		if (gracefulShutdown)
			logger.error("completed Shutdown!");
	} catch (RuntimeException& e) {
		logger.error(e.message());
	}  catch (IOException& e) {
		ReleaseResource::pointer<Webserv>(webserv);
		logger.error(e.message());
	}
	ReleaseResource::pointer<Webserv>(webserv);
	return (0);
}