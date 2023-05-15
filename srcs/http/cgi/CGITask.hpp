#ifndef CGITASK_HPP
#define CGITASK_HPP

// #include "../parse/Parser.hpp"
// #include <http/task/HTTPTask.hpp>
#include "../../file/FileDescriptor.hpp"
#include "../server/RWCallback.hpp"
#include <stddef.h>

class CommonGatewayInterface;
class HTTPClient;

class CGITask : public RWCallback {
	private:
		HTTPClient& _client;
		CommonGatewayInterface& _cgi;
		FileDescriptor& _out;
		Parser _parser;
		size_t wroteBodyUpTo;
		bool _running;
		bool _nextCalled;

	private:
		CGITask(void);
		CGITask(const CGITask &other);
		CGITask& operator=(const CGITask &other);

	public:
		CGITask(HTTPClient &client, CommonGatewayInterface &cgi);
		virtual ~CGITask(void);
		bool running();
		bool recv(FileDescriptor &fd);
		bool send(FileDescriptor &fd);	
		bool isDone();
		bool hasReadHeaders();
		FileDescriptor& out();
		bool timeoutTouch();
};

#endif
