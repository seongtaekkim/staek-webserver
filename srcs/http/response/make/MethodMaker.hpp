#ifndef METHODMAKER_HPP
#define METHODMAKER_HPP

#include "IMaker.hpp"
#include "../../../util/Singleton.hpp"
#include "../../../log/LogFactory.hpp"
#include "ResponseMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"

// class IMaker;
class ResponseMaker;

class MethodMaker : public IMaker, public Singleton<MethodMaker> {
public:
	MethodMaker(void);
	MethodMaker(const MethodMaker& other);
	MethodMaker& operator=(const MethodMaker& other);
	virtual ~MethodMaker(void);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
