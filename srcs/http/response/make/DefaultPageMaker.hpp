#ifndef DEFAULTPAGEMAKER_HPP
#define DEFAULTPAGEMAKER_HPP

#include "../../../util/Singleton.hpp"
#include "ResponseMaker.hpp"
#include "IMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"

class DefaultPageMaker : public IMaker, public Singleton<DefaultPageMaker> {
public:
	DefaultPageMaker(void);
	DefaultPageMaker(const DefaultPageMaker &other);
	virtual ~DefaultPageMaker(void);
	DefaultPageMaker& operator=(const DefaultPageMaker &other);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
