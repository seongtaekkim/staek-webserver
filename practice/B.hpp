#ifndef B_HPP
#define B_HPP
#include "Callback.hpp"

class B {
private:
	Callback& _c;
public:
	B(Callback& c);
	void dofunc();
};
#endif