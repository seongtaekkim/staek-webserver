#ifndef IMAKER_HPP
#define IMAKER_HPP

// #include "../Response.hpp"
// #include "../../request/Request.hpp"
// #include "../../server/Client.hpp"
// #include "ResponseMaker.hpp"

class Client;
class Request;
class Response;
class ResponseMaker;

class IMaker {
public:
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker) = 0;
	virtual ~IMaker(void);
};

#endif