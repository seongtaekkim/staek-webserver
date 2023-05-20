#ifndef CGIMAKER_HPP
#define CGIMAKER_HPP

#include "../../../util/Singleton.hpp"
#include "ResponseMaker.hpp"
#include "IMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"

class CGIMaker : public IMaker, public Singleton<CGIMaker> {
public:
	CGIMaker(void);
	CGIMaker(const CGIMaker &other);
	virtual ~CGIMaker(void);
	CGIMaker& operator=(const CGIMaker& other);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
