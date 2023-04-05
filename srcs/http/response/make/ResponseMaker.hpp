#ifndef RESPONSEMAKER_HPP
#define RESPONSEMAKER_HPP


// #include "../Response.hpp"
// #include "../../request/Request.hpp"
// #include "../../server/Client.hpp"
#include <queue>

class Request;
class Response;
class Client;
class IMaker;

class ResponseMaker {

private:
	Request&				_req;
	Response&			_res;
	Client&				_client;
	std::queue<IMaker*>	_maker;

	ResponseMaker(void);
	ResponseMaker& operator=(const ResponseMaker& other);
public:
	ResponseMaker(const ResponseMaker& other);
	ResponseMaker(Request& req, Response& res, Client& client);
	virtual ~ResponseMaker(void);
	void setMaker(void);
	void executeMaker(void);
	void popMaker(void);

};

#endif