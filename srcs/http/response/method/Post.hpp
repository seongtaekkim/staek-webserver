#ifndef POST_HPP
#define POST_HPP

#include "IMethod.hpp"

class Post : public IMethod {
private:
public:
	Post(const Post& other);
	Post& operator=(const Post& other);
	Post(void);
	virtual ~Post(void);
    static Post* instance() {
        static Post instance;
        return (&instance);
    }
	virtual void doMethod(Request &req, Response &res, Client &cli);
	virtual void setHasBody(bool hasbody);
	virtual bool getHasBody();
};

#endif