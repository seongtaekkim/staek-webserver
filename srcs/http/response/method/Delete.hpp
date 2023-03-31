#ifndef DELETE_HPP
#define DELETE_HPP

#include "IMethod.hpp"

class Delete : public IMethod {
private:
public:
	Delete(const Delete& other);
	Delete& operator=(const Delete& other);
	Delete(void);
	virtual ~Delete(void);
    static Delete* instance() {
        static Delete instance;
        return (&instance);
    }
	virtual void doMethod(void);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
};

#endif