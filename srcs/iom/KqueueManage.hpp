#ifndef KQUEUEMANAGE_HPP
#define KQUEUEMANAGE_HPP

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "../util/Singleton.hpp"
#include <map>
#include <vector>
#include <string>
#include "../http/server/RWCallback.hpp"

/**
 * @brief kqueue 객체 관리
 * @details 싱글톤으로 관리된다.
 * @author seongtki
 * @date 2023.03.26
 */
class KqueueManage : public Singleton<KqueueManage> {
public:
	typedef std::map<int ,RWCallback*> _CallbackMap;
	enum { ACCEPT = 1, READ = 2, WRITE = 3 };
private:

	int 						_kqueueFd;
	struct kevent*				_currEv;
	// std::map<int, std::string>	_clientMap; // map for client socket:data
    std::vector<struct kevent>	_changeVec; // kevent vector for changelist
    struct kevent				_eventArr[8]; // kevent array for eventlist
	int							_eventCount;
	_CallbackMap				_callbackMap;

	KqueueManage(const KqueueManage& other);
	KqueueManage& operator=(const KqueueManage& other);
public:
	~KqueueManage(void);
	KqueueManage(void);
	void setEvent(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
	void kevent(void);
	int eventCount(void) const;
	void create(FileDescriptor& fd, RWCallback& callback, int opt);
	//void update()
	void run(void);
	std::vector<struct kevent>	changeVec(void) const;
	struct kevent* eventArr();
};

#endif