#ifndef ERRORPAGEMAKER_HPP
#define ERRORPAGEMAKER_HPP

#include "../../../util/Singleton.hpp"
#include "../../../exception/IOException.hpp"
#include "ResponseMaker.hpp"
#include "IMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"

// class Logger;

class ErrorPageMaker :public IMaker, public Singleton<ErrorPageMaker> {
public:
	// static Logger &LOG;

public:
	ErrorPageMaker(void);
	ErrorPageMaker(const ErrorPageMaker &other);
	virtual ~ErrorPageMaker(void);
	ErrorPageMaker& operator=(const ErrorPageMaker &other);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
