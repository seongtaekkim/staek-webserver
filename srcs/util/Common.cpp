
#include <iostream>

template<typename T>
void safe_delete(T **p) {
	if (*p)
		delete (*p);
	*p = NULL;
}