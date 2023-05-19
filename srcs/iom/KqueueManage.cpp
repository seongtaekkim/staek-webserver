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

using namespace std;

void exit_with_perror(const string& msg)
{
    cerr << msg << endl;
    exit(EXIT_FAILURE);
}

void change_events(vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata) {
    struct kevent temp_event;

    EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
    change_list.push_back(temp_event);
	// std::cout << "temp_event 	: " << temp_event.ident << std::endl;
}

void disconnect_client(int client_fd, map<int, string>& clients)
{
    cout << "client disconnected: " << client_fd << endl;
    close(client_fd);
    clients.erase(client_fd);
}

KqueueManage::KqueueManage(void) {
	std::cout << "kqieie init " << std::endl;
	if ((this->_kqueueFd = ::kqueue()) == -1)
        throw IOException("kqueue() error : ", errno);
}

KqueueManage::~KqueueManage(void) {}


void KqueueManage::setEvent(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata) {
 	struct kevent temp_event;
	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	// std::cout << "setevent : " << temp_event.ident << " size :  " << this->_changeVec.size() << std::endl;
	this->_changeVec.push_back(temp_event);
}

void KqueueManage::delEvent(int fd) {
	std::vector<struct kevent>::iterator bit = this->_changeVec.begin();
	for (std::vector<struct kevent>::iterator i = bit ; i !=  this->_changeVec.end() ; ++i) {
		if ((*i).ident == fd) {
			EV_SET(&(*i), fd, EVFILT_READ, EV_DELETE | EV_ENABLE , 0, 0, NULL);
			EV_SET(&(*i), fd, EVFILT_WRITE, EV_DELETE | EV_ENABLE, 0, 0, NULL);
			std::cout << "delEvent : " << fd <<  std::endl;

			this->_changeVec.erase(i);
			 --i;
		}
	}
	::close(fd);
	this->_callbackMap.erase(fd);
	this->_fdMap.erase(fd);
}

void KqueueManage::kevent() {
	struct timespec myTime  = {1, 0};
	
	this->_eventCount = ::kevent(this->_kqueueFd, &this->_changeVec[0]
							, this->_changeVec.size() , this->_eventArr, 300, &myTime);
	// if (this->_eventCount == -1)
		// throw IOException("kevent() error : ", errno);
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

void KqueueManage::create(FileDescriptor& fd, RWCallback& callback) {
	std::cout << "KqueueManage::create : " << fd.getFd() << std::endl;
	int raw = fd.getFd();
	this->_callbackMap[raw] = &callback;
	this->_fdMap[raw] = &fd;
}

bool KqueueManage::recv(int fd) {
	std::cout << _fdMap.size() << std::endl;
	std::cout << _callbackMap.size() << std::endl;
	bool b = this->_callbackMap[fd]->recv(*this->_fdMap[fd]);
	return (b);
}

bool KqueueManage::send(int fd) {
	std::cout << "KqueueManage::send : " << fd << std::endl;
	bool b;
	if (!this->_callbackMap[fd]) {
		std::cout << "KqueueManage::send : _callbackMap" << fd << std::endl;
		return (true);
	}
	b = this->_callbackMap[fd]->send(*this->_fdMap[fd]);
	return (b);
}
