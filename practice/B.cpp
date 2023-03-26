#include "B.hpp"
#include "A.hpp"

B::B(Callback& c) : _c(c) {

}

void B::dofunc() {
	this->_c.recv();
}