#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(int fd) : _fd(fd), _valid(false), _isClosed(false) {}

FileDescriptor::~FileDescriptor() {
	if (!this->_isClosed && this->_valid)
		::close(this->_fd);
}

ssize_t FileDescriptor::read(void *buf, std::size_t nbyte) {
	this->validateNotClosed();
	ssize_t ret = ::read(this->_fd, buf, nbyte);
	if (!this->_valid && ret != -1)
		this->_valid = true;
	return (ret);
}

ssize_t FileDescriptor::write(const void *buf, std::size_t nbyte) {
	this->validateNotClosed();
	ssize_t ret = ::write(this->_fd , buf, nbyte);
	if (!this->_valid && ret != -1)
		this->_valid = true;
	return (ret);
}

/**
* @brief lseek함수 재정의.
		 lseek 함수 전후로 예외처리를 추가함.
		 lseek : 파일 커서(seek pointer) 조정함수
* @return success : Seek pointer 위치, 에러 시 -1 리턴
* @param  whence(기준점, SEEK_SET(0) : 파일의 맨 앞
					  SEEK_CUR(1) : 현재 Seek 포인터
					SEEK_END(2) : 파일의 맨 끝)
		  offset(기준점으로부터 동할 거리)
* @date 2023.03.23
*/
off_t FileDescriptor::lseek(off_t offset, int whence) {
	this->validateNotClosed();
	return (::lseek(this->_fd, offset, whence)); // exception 추가해야함.. 종류생각해야함
}

void FileDescriptor::close() {
	this->validateNotClosed();
	::close(_fd);
	_isClosed = true;
}


/**
* @brief fd nonblock 설정.
* @exception fcntl함수 실패 시 IOException 발생
* @date 2023.03.23
*/
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

/**
* @brief fd close 여부 체크.
* @exception 이미 닫혀있다면 IllegalStateException 발생
* @date 2023.03.23
*/
void FileDescriptor::validateNotClosed(void) const {
	if (_isClosed)
		throw IllegalStateException("fd was closed");
}