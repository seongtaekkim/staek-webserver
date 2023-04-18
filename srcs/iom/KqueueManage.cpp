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
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
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
			this->_changeVec.erase(i);
			 --i;
		}
	}
	::close(fd);
	std::cout << "disconnected" << std::endl;
	//	KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

}

void KqueueManage::kevent() {
	this->_eventCount = ::kevent(this->_kqueueFd, &this->_changeVec[0]
							, this->_changeVec.size() , this->_eventArr, 8, NULL);
	if (this->_eventCount == -1)
		throw IOException("kevent() error : ", errno);
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

void KqueueManage::create(FileDescriptor& fd, RWCallback& callback, int opt) {
	int raw = fd.getFd();

	//addToSets(fd.raw(), operations);

	//this->_callbackMap[raw] = &callback;

	//this->_callbackMap[raw]->recv()
	// m_fileDescriptors[raw] = &fd;
	
}

void KqueueManage::run() {

}
