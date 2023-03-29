#ifndef RWCALLBACK_HPP
#define RWCALLBACK_HPP

#include "../../file/FileDescriptor.hpp"

class RWCallback {
public:
	virtual ~RWCallback();
	virtual bool recv(FileDescriptor &fd);
	virtual bool send(FileDescriptor &fd);	
};

#endif