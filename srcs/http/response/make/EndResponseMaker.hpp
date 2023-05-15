#ifndef ENDRESPONSEMAKER_HPP
#define ENDRESPONSEMAKER_HPP

#include "IMaker.hpp"
#include "../../../util/Singleton.hpp"
#include "../../../log/LogFactory.hpp"
#include "ResponseMaker.hpp"
#include "../../server/Client.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"
#include <iostream>
#include "../../Header.hpp"
#include "../../../iom/KqueueManage.hpp"

class EndResponseMaker : public IMaker, public Singleton<EndResponseMaker> {
public:
	EndResponseMaker(void);
	EndResponseMaker(const EndResponseMaker &other);
	virtual  ~EndResponseMaker(void);
	EndResponseMaker& operator=(const EndResponseMaker &other);
	virtual void make(Client& client, Request& req, Response& res, ResponseMaker& maker);
};

#endif
