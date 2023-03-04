
#ifndef SERVCONTEXT_HPP
#define SERVCONTEXT_HPP

#include "Common.hpp"

class ServContext {
private:
	Tokens		tokens;
	Listens		listens;
	Methods		methods;
	ErrorPages	errorPages;
	
public:
	ServContext(void);
};

#endif