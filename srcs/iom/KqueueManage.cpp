#include "KqueueManage.hpp"
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <vector>
#include "../http/server/Server.hpp"
#include "../config/block/ServerBlock.hpp"
#include <list>
#include "../exception/IOException.hpp"

KqueueManage::KqueueManage(void) {
	if ((this->_kqueueFd = ::kqueue()) == -1)
        throw IOException("kqueue() error : ", errno);
}

KqueueManage::~KqueueManage(void) {}

void KqueueManage::setEvent(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata) {
 	struct kevent temp_event;
	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	this->_changeVec.push_back(temp_event);
}

void KqueueManage::delEvent(int fd) {
	std::vector<struct kevent>::iterator bit = this->_changeVec.begin();
	for (std::vector<struct kevent>::iterator i = bit ; i !=  this->_changeVec.end() ; ++i) {
		if ((*i).ident == (unsigned long)fd) {
			EV_SET(&(*i), fd, EVFILT_READ, EV_DELETE | EV_ENABLE , 0, 0, NULL);
			EV_SET(&(*i), fd, EVFILT_WRITE, EV_DELETE | EV_ENABLE, 0, 0, NULL);

			this->_changeVec.erase(i);
			 --i;
		}
	}
	::close(fd);
	this->_callbackMap.erase(fd);
	this->_fdMap.erase(fd);
	this->_serverFdMap.erase(fd);
}

void KqueueManage::kevent() {
	struct timespec myTime  = {1, 0};
	this->_eventCount = ::kevent(this->_kqueueFd, &this->_changeVec[0]
							, this->_changeVec.size() , this->_eventArr, 300, &myTime);

}

int KqueueManage::eventCount(void) const {
	return (this->_eventCount);
}

std::vector<struct kevent>
KqueueManage::changeVec(void) const {
	return (this->_changeVec);
}

struct kevent* KqueueManage::eventArr() {
	return (this->_eventArr);
}

void KqueueManage::create(FileDescriptor& fd, RWCallback& callback, int serverFd) {
	int raw = fd.getFd();
	this->_callbackMap[raw] = &callback;
	this->_fdMap[raw] = &fd;
	this->_serverFdMap[raw] = serverFd;
}

bool KqueueManage::recv(int fd) {
	bool b = false;
	if (this->_callbackMap[fd])
		b = this->_callbackMap[fd]->recv(*this->_fdMap[fd]);
	return (b);
}

bool KqueueManage::send(int fd) {
	bool b;
	if (!this->_callbackMap[fd]) {
		return (true);
	}
	b = this->_callbackMap[fd]->send(*this->_fdMap[fd]);
	return (b);
}

int KqueueManage::serverFd(int fd) {
	if (this->_serverFdMap[fd])
		return (this->_serverFdMap[fd]);
	return (-1);
}