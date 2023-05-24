#ifndef GET_HPP
#define GET_HPP

#include "IMethod.hpp"
#include "../HTTPStatus.hpp"

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
	virtual bool doMethod(Request &req, Response &res, Client &cli);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
	std::string listing(const URL& url, const File& file);
};

#endif