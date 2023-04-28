#ifndef FILEDESCRIPTOR_HPP
#define FILEDESCRIPTOR_HPP

#include <stddef.h>
#include <sys/types.h>
#include <iostream>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "../exception/IllegalStateException.hpp"
#include "../exception/IOException.hpp"
#include "../util/Storage.hpp"

// 객체 생성할 때 nonblock 설정해주도록 고려해보자
/**
 * 
 * @brief file descriptor 관리
 * @details 소켓통신, io 통신에 사용할 file descriptor 관리객체.
 * @author seongtki
 * @date 2023.03.22
 */
class FileDescriptor : public Storage {
protected:
	int		_fd;
	bool	_valid;
	bool	_isClosed;

private:
	FileDescriptor(void);
	FileDescriptor(const FileDescriptor &other);
	FileDescriptor& operator=(const FileDescriptor &other);
public:
	FileDescriptor(int fd);
	virtual ~FileDescriptor();
	ssize_t read(void *buf, std::size_t nbyte);
	ssize_t write(const void *buf, std::size_t nbyte);
	off_t	lseek(off_t offset, int whence);
	void	close(void);
	void	setNonBlock(void);
	int		getFd(void) const;
	bool	isClosed(void) const;
	void	validateNotClosed(void) const;
};

#endif