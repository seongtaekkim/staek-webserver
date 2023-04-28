#include "ResponseByFile.hpp"
#include "../../iom/KqueueManage.hpp"
// #include <util/Singleton.hpp>
#include <iostream>

ResponseByFile::ResponseByFile(FileDescriptor& fd, std::size_t contentLength) :
		_fd(fd), _contentLength(contentLength), _store(0), _isEnd(false) {
	KqueueManage::instance().create(fd, *this);
	KqueueManage::instance().setEvent(fd.getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

ResponseByFile::~ResponseByFile() {
	KqueueManage::instance().delEvent(this->_fd.getFd());
	// delete &_fd;
}

bool ResponseByFile::store(Storage& storage) {
	storage.store(_fd);
	return (true);
}

bool ResponseByFile::recv(FileDescriptor& fd) {
	(void)fd;
	char buf[SHTTP::DEFAULT_READSIZE];
	ssize_t r = this->_fd.read(buf, SHTTP::DEFAULT_READSIZE);
	if (r != -1)
		_store += r;
	// else
	// {	
	// 	std::size_t diff = _contentLength - _store;
	// 	if (diff)
	// 		_store += _fd.storeZeros(diff);
	// }
	_fd.store(std::string(buf));
	std::cout << " ResponseByFile::" << r << std::endl;
	std::cout << buf << std::endl;
	if (r <= 0)
		return (false);
	this->_isEnd = true;
	return (true);
}

bool ResponseByFile::isEnd(void) {
	return (this->_isEnd);
}