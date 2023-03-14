#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(int fd) : _fd(fd) {}

FileDescriptor::~FileDescriptor() {}

ssize_t FileDescriptor::read(void *buf, size_t nbyte) {
	this->validateNotClosed();
	ssize_t ret = ::read(this->_fd, buf, nbyte);
	if (!this->_valid && ret != -1)
		this->_valid = true;
	return (ret);
}

ssize_t FileDescriptor::write(const void *buf, size_t nbyte) {
	this->validateNotClosed();
	ssize_t ret = ::write(this->_fd , buf, nbyte);
	if (!this->_valid && ret != -1)
		this->_valid = true;
	return (ret);
}

/**
* @brief 요청인자에 해당하는 로그 컨테이너를 리턴한다.
		컨테이너에 없다면, 생성 후 리턴한다.
* @return success : Seek pointer 위치, 에러 시 -1 리턴하고 errno 설정
* @param offset : , whence : ,
* @date 2023.03.23
*/
off_t FileDescriptor::lseek(off_t offset, int whence) {
	this->validateNotClosed();
	return (::lseek(this->_fd, offset, whence)); // exception 추가
}

void FileDescriptor::close() {
	this->validateNotClosed();
	::close(_fd);
	_isClosed = true;
}

void FileDescriptor::setNonBlock() {
	if (::fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1)
		throw IOException("fail fcntl setting", errno);
	this->_valid = true;
}

int FileDescriptor::getFd() const {
	return (_fd);
}

bool FileDescriptor::isClosed() const {
	return (_isClosed);
}

void FileDescriptor::validateNotClosed(void) const {
	if (_isClosed)
		throw IllegalStateException("fd was closed");
}