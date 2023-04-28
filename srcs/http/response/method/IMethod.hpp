#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include "../../server/Client.hpp"
#include "../../request/Request.hpp"
#include "../Response.hpp"

class IMethod {
protected:
	bool _hasBody;

public:
	IMethod(void);
	IMethod(const IMethod& other);
	IMethod& operator=(const IMethod& other);
	virtual ~IMethod(void);
	virtual bool doMethod(Request &req, Response &res, Client &cli) = 0;
	virtual void setHasBody(bool hasbody) = 0;
	virtual bool getHasBody(void) = 0;
};

#endif