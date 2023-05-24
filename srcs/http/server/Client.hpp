#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../address/InetAddress.hpp"
#include "../../file/FileDescriptor.hpp"
#include "Socket.hpp"
#include "Server.hpp"
#include "RWCallback.hpp"
#include "SocketStorage.hpp"
#include "../request/Request.hpp"
#include "../response/Response.hpp"
#include "../response/HTTPStatus.hpp"
#include "../response/make/ResponseMaker.hpp"
#include "../../exception/Exception.hpp"
#include "../../iom/KqueueManage.hpp"
#include "../response/StatusLine.hpp"
#include "../parse/Parser.hpp"
#include "../parse/PathParser.hpp"
#include "../../exception/Exception.hpp"
#include "../response/method/PutTask.hpp"
#include "../cgi/CGITask.hpp"
#include "../../util/Time.hpp"
#include "../cgi/CGI.hpp"

class Server;
/**
 * @brief 클라이언트 관리
 * @details connection
 * @author seongtki
 * @date 2023.03.26
 */

// class ResponseMaker;
class Response;
class Request;
class PutTask;
class CGITask;
class Parser;

class Client : public RWCallback {
public:
	static int	_s_connCnt;
	enum { HEADER, BODY, END };
private:
	InetAddress		_inetAddress;
	Server&			_server;
	Socket&			_socket;
	std::string 	_body;
	SocketStorage 	_in;
	SocketStorage 	_out;
	Request			_req;
	Response 		_res;
	ResponseMaker	_maker;
	bool 			_isKeepAlive;
	int				_currProgress;
	Parser			_parser;
	PathParser		_pathParser;

	PutTask*		_putTask;
	CGITask*		_cgiTask;

	unsigned long	_lastTime;

	Client(void);
	Client& operator=(const Client& other);
public:
	Client(const Client& other);
	virtual ~Client(void);
	Client(InetAddress inetAddress, Server& server, Socket& socket);
	Socket& socket() const;
	bool recv(FileDescriptor& fd);
	bool send(FileDescriptor& fd);

	bool progress(void);
	bool progressHead(void);
	bool progressBody(void);
	Server& server(void);

	int state(void);
	Parser& parser(void);
	Response& response(void);
	Request& request(void);
	ResponseMaker& maker(void);
	void fileWrite(PutTask& task);
	void cgiWrite(CGITask& task);
	PutTask* fileWrite(void);
	CGITask* cgiWrite(void);
	std::string& body(void);
	SocketStorage& in(void);
	SocketStorage& out(void);
	void end(void);
	InetAddress inetAddress(void) const;
	void updateTime(void);
	unsigned long lastTime(void) const;
	unsigned long clientMaxBodySize(const ServerBlock* serverBlock, const LocationBlock* locationBlock);

public:
	static void deny(Client& client);
};

#endif