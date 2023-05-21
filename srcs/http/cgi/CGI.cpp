#include "CGI.hpp"
#include "CGITask.hpp"
#include "../../config/Config.hpp"
#include <sys/signal.h>
#include <signal.h>
#include <sys/wait.h>
#include "../../exception/IOException.hpp"
#include "../response/method/Method.hpp"
#include "../SHTTP.hpp"
#include "../Header.hpp"
#include "../server/Client.hpp"
#include "../server/Server.hpp"
#include "../request/Request.hpp"
#include "../../file/File.hpp"
#include <sys/errno.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "../../util/Base.hpp"
#include "../../util/ReleaseResource.hpp"
#include "../../util/Replace.hpp"
#include "../URL.hpp"
#include "../../main.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>


const std::string CGI::ENV_AUTH_TYPE = "AUTH_TYPE";
const std::string CGI::ENV_CONTENT_LENGTH = "CONTENT_LENGTH";
const std::string CGI::ENV_CONTENT_TYPE = "CONTENT_TYPE";
const std::string CGI::ENV_GATEWAY_INTERFACE = "GATEWAY_INTERFACE";
const std::string CGI::ENV_PATH_INFO = "PATH_INFO";
const std::string CGI::ENV_PATH_TRANSLATED = "PATH_TRANSLATED";
const std::string CGI::ENV_QUERY_STRING = "QUERY_STRING";
const std::string CGI::ENV_REMOTE_ADDR = "REMOTE_ADDR";
const std::string CGI::ENV_REMOTE_PORT = "REMOTE_PORT";
const std::string CGI::ENV_REMOTE_IDENT = "REMOTE_IDENT";
const std::string CGI::ENV_REMOTE_USER = "REMOTE_USER";
const std::string CGI::ENV_REQUEST_METHOD = "REQUEST_METHOD";
const std::string CGI::ENV_REQUEST_URI = "REQUEST_URI";
const std::string CGI::ENV_SCRIPT_FILENAME = "SCRIPT_FILENAME";
const std::string CGI::ENV_SCRIPT_NAME = "SCRIPT_NAME";
const std::string CGI::ENV_SERVER_NAME = "SERVER_NAME";
const std::string CGI::ENV_SERVER_PORT = "SERVER_PORT";
const std::string CGI::ENV_SERVER_PROTOCOL = "SERVER_PROTOCOL";
const std::string CGI::ENV_SERVER_SOFTWARE = "SERVER_SOFTWARE";
const std::string CGI::REDIRECT_STATUS = "REDIRECT_STATUS";

CGI::CGI(pid_t pid, FileDescriptor& in, FileDescriptor& out, File& file) :
		_pid(pid), _in(in), _out(out), _file(file), _killed(false) {}

CGI::~CGI(void) {
	std::cout << "CGI::~CGI : " << std::endl; 
	// _file.remove();
	delete &_in;
	delete &_out;
	kill();
}

void CGI::kill(void) {
	if (!_killed) {
		_killed = true;
		::kill(_pid, SIGKILL);
	}
}

void CGI::wait() {
	if (!_killed)
		waitpid(_pid, NULL, 0);
}

bool CGI::running() {
	int status;
	if (::waitpid(_pid, &status, WNOHANG) == -1) {
		errno = 0;
		return (false);
	}
	if (WIFEXITED(status))
		return (false);
	if (::kill(_pid, 0) == -1) {
		errno = 0;
		return (false);
	}
	return (true);
}

CGITask* CGI::execute(Client& client, const ServerBlock::CgiType& cgiBlock, const SEnvironment& environment) {
	int inPipe[2];
	if (::pipe(inPipe) == -1)
		throw IOException("in pipe exception", errno);

std::cerr << "start 11" << std::endl;
std::cerr << "start 11" << client.inetAddress().address() << std::endl;

	SEnvironment env = environment;

	Request& request = client.request();
std::cerr << "start 11" << std::endl;

	File scriptFile(request.resource());
	File scriptRelativeFile(request.root(), scriptFile);
	File scriptAbsoluteFile(scriptRelativeFile);

	if (scriptAbsoluteFile.path().c_str()[0] != '/')
		scriptAbsoluteFile = File(File::currentDir(), scriptAbsoluteFile.path());


  	File _tmp(SHTTP::DEFAULT_TMP_FILE + Base::toString(client.socket().getFd(), 10));
  	FileDescriptor* _fileFd = _tmp.open( O_APPEND | O_CREAT | O_RDWR, 0777);
	_fileFd->setNonBlock();

    std::string appName;
    appName.append(APPLICATION_NAME).append("/").append(APPLICATION_VERSION);
std::cerr << "start 112 " <<  env.size() << std::endl;
	env.appendOne(ENV_GATEWAY_INTERFACE, "CGI/1.1");
std::cerr << "start 11" <<  client.inetAddress().address() << std::endl;
	env.appendOne(ENV_REMOTE_ADDR, client.inetAddress().address());
	env.appendOne(ENV_REMOTE_PORT, Base::toString(client.inetAddress().port(), 10));
	env.appendOne(ENV_REQUEST_METHOD, client.parser().method());
	env.appendOne(ENV_REQUEST_URI, request.url().path());
	env.appendOne(ENV_SCRIPT_FILENAME, scriptAbsoluteFile.path());
	env.appendOne(ENV_SCRIPT_NAME, request.url().path());
	// env.appendOne(ENV_SERVER_NAME, client.httpServer().host()); 
	env.appendOne(ENV_SERVER_NAME, "127.0.0.1");
	// env.appendOne(ENV_SERVER_PORT, Convert::toString(client.httpServer().port()));
	env.appendOne(ENV_SERVER_PORT, "8080");
	env.appendOne(ENV_SERVER_PROTOCOL, SHTTP::VERSION());
	env.appendOne(ENV_SERVER_SOFTWARE, appName);
	env.appendOne(ENV_PATH_INFO, request.url().path());
	env.appendOne(ENV_PATH_TRANSLATED, scriptAbsoluteFile.path());
	env.appendOne(ENV_QUERY_STRING, request.url().queryString());

	IMethod* method = Method::METHOD[client.parser().method()];
	if (method->getHasBody()) {
		env.appendOne(ENV_CONTENT_LENGTH, Base::toString(client.body().length(), 10));
		std::string contentType = client.response().header().get(Header::CONTENT_TYPE);
		if (contentType.size() > 0)
			env.appendOne(ENV_CONTENT_TYPE, contentType);
	}
	env.appendOne(REDIRECT_STATUS, "200");

	// const AuthBlock* authBlockOpt = request.authBlock();
	// if (authBlockOpt.present())
	// {
	// 	const AuthBlock &authBlock = *authBlockOpt.get();

	// 	env.appendOne(ENV_AUTH_TYPE, authBlock.prettyType());

	// 	const BasicAuthBlock *basicAuthBlock = dynamic_cast<BasicAuthBlock const*>(&authBlock);
	// 	if (basicAuthBlock)
	// 	{
	// 		env.appendOne(ENV_REMOTE_USER, basicAuthBlock->user());
	// 		env.appendOne(ENV_REMOTE_IDENT, basicAuthBlock->user());
	// 	}
	// }
	std::cerr << "start 11" << std::endl;
	const Header& header = client.parser().header();
	for (Header::mconst_iterator it = header.begin(); it != header.end(); it++)
		env.appendOne("HTTP_" + Base::toUpper(Replace::replace(Replace::replace(it->first, "=", "_"), "-", "_")), it->second.front());

	char **envp = env.mapToChar();

	pid_t pid = ::fork();
	if (pid == -1) {
		int err = errno;

		ReleaseResource::pointer2th<char>(envp);

		::close(inPipe[0]);
		::close(inPipe[1]);
		throw IOException("fork", err);
	}
	if (pid == 0) {
		std::string path = File(request.root(), cgiBlock.second).path();
		
		if (path.c_str()[0] != '/')
			path = File(File::currentDir(), path).path();

		std::string file = request.resource().c_str()[0] == '/' ? request.resource().substr(1) : request.resource();

		::chdir(request.root().c_str());

		::dup2(inPipe[0], 0);
		::dup2(_fileFd->getFd(), 1);

		::close(inPipe[1]);
		::close(inPipe[0]);

		char *const argv[] = {const_cast<char*>(path.c_str()), const_cast<char*>(file.c_str()), NULL};
		// std::cerr << "start child pid : " <<  path.c_str() <<  " " << file.c_str() << " " << request.root().c_str() << _fileFd->getFd()  <<  std::endl;
		::execve(path.c_str(), argv, envp);
		
		std::cerr << "Status: 500\r\n\r\nFAILED TO RUN CGI\n" << path << "\n" << std::strerror(errno) << std::flush;
		::exit(1);
		return (NULL);
	} else {
		ReleaseResource::pointer2th<char>(envp);

		::close(inPipe[0]);
		// ::close(inPipe[1]);
		FileDescriptor *stdin = NULL;
		FileDescriptor *stdout = NULL;
		CGI *cgi = NULL;
		CGITask *cgiTask = NULL;

		try {
			stdin = new FileDescriptor(inPipe[1]);
            stdin->setNonBlock();

			int status;
			// if (::waitpid(pid, &status, WNOHANG) == -1) {
			// 	errno = 0;
			// 	return (NULL);
			// }
			// if (WIFEXITED(status))
			// 	return (NULL);

			// ::close(_fileFd->getFd());
			
  			// FileDescriptor* _fileFd = _tmp.open(O_RDONLY, 0777);
			// char* c2;
			// std::cout << "!!!!!!!!!?"  << _fileFd->getFd()  << " " << inPipe[0] << std::endl;
			// _fileFd->read(c2, 300000);
			// std::cout << "startdataa : " << c2 << std::endl;
			// _fileFd->lseek(0, SEEK_SET);

			cgi = new CGI(pid, *stdin, *_fileFd, _tmp);
			cgiTask = new CGITask(client, *cgi);
	
			return (cgiTask);
		} catch (...) {
			::kill(pid, SIGKILL);
			if (stdin)
				delete stdin;
			else
				::close(inPipe[1]);
			if (stdout)
				delete stdout;
			ReleaseResource::pointer(cgi);
			ReleaseResource::pointer(cgiTask);
			throw;
		}
	}
}
