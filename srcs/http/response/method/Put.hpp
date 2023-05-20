#ifndef PUT_HPP
#define PUT_HPP

#include "IMethod.hpp"
#include "../../../file/File.hpp"

class Put : public IMethod {
public:
	Put(const Put& other);
	Put& operator=(const Put& other);
	Put(void);
	virtual ~Put(void);
    static Put* instance() {
        static Put instance;
        return (&instance);
    }
	virtual bool doMethod(Request &req, Response &res, Client &cli);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
};

#endif
