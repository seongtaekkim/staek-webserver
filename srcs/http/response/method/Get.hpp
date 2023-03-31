#ifndef GET_HPP
#define GET_HPP

#include "IMethod.hpp"

class Get : public IMethod {
private:
public:
	Get(const Get& other);
	Get& operator=(const Get& other);
	Get(void);
	virtual ~Get(void);
    static Get* instance() {
        static Get instance;
        return (&instance);
    }
	virtual void doMethod(void);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
};

#endif