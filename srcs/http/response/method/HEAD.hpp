#ifndef HEAD_HPP
#define HEAD_HPP

#include "IMethod.hpp"

class HEAD : public IMethod {
public:
	HEAD(const HEAD& other);
	HEAD& operator=(const HEAD& other);
	HEAD(void);
	virtual ~HEAD(void);
    static HEAD* instance() {
        static HEAD instance;
        return (&instance);
    }
	virtual bool doMethod(Request &req, Response &res, Client &cli);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
};

#endif
