#ifndef A_HPP
#define A_HPP

#include "Callback.hpp"
#include <iostream>
class A : public Callback {
private:
public:
	virtual bool recv();
	virtual bool send();
};

#endif