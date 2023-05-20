#ifndef INTERCEPTORMAKER_HPP
#define INTERCEPTORMAKER_HPP

#include "../../../util/Singleton.hpp"
#include "../../../exception/IOException.hpp"
#include "ResponseMaker.hpp"
#include "IMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"

class InterceptorMaker : public IMaker, public Singleton<InterceptorMaker> {
public:
	InterceptorMaker(void);
	InterceptorMaker(const InterceptorMaker &other);
	virtual ~InterceptorMaker(void);
	InterceptorMaker& operator=(const InterceptorMaker &other);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
