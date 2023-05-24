#ifndef CGITASK_HPP
#define CGITASK_HPP

#include "../parse/Parser.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../server/RWCallback.hpp"
#include <stddef.h>

class CGI;
class Client;

class CGITask : public RWCallback {
	private:
		Client&					_client;
		CGI&					_cgi;
		size_t					wroteBodyUpTo;
		bool					_running;
	private:
		CGITask(void);
		CGITask(const CGITask &other);
		CGITask& operator=(const CGITask &other);

	public:
		CGITask(Client &client, CGI &cgi);
		virtual ~CGITask(void);
		bool running();
		bool recv(FileDescriptor &fd);
		bool send(FileDescriptor &fd);	
		bool isDone();
		bool hasReadHeaders();
		FileDescriptor& out();
		bool timeoutTouch();
		inline CGI& cgi(void)  const {
			return (this->_cgi);
		}
};

#endif
