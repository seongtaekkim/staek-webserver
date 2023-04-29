#ifndef IBODY_HPP
#define IBODY_HPP

#include "../../util/Storage.hpp"

class IBody {
public:
	virtual ~IBody();
	virtual bool store(Storage& storage) = 0;
	virtual bool isEnd(void) = 0;
};

#endif
