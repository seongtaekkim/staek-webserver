#ifndef SOCKETSTORAGE_HPP
#define SOCKETSTORAGE_HPP

#include "../../util/Storage.hpp"

class SocketStorage : public Storage {
public:
	SocketStorage(void);
	SocketStorage(const SocketStorage& other);
	SocketStorage& operator=(const SocketStorage& other);
	virtual ~SocketStorage(void);
	void recv();
	void send();
};

#endif