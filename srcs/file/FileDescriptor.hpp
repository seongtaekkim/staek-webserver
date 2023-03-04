#ifndef FILEDESCRIPTOR_HPP
#define FILEDESCRIPTOR_HPP

#include <stddef.h>
#include <sys/types.h>

class FileDescriptor {
protected:
	int		_fd;
	bool	_verified :1;
	bool	_closed :1;

private:
	FileDescriptor(void);
	FileDescriptor(const FileDescriptor &other);

	FileDescriptor&
	operator=(const FileDescriptor &other);
public:
	FileDescriptor(int fd);
	virtual ~FileDescriptor();
	ssize_t read(void *buf, size_t nbyte);
	ssize_t write(const void *buf, size_t nbyte);
	off_t	lseek(off_t offset, int whence);
	off_t	seekToEnd();
	void	close();
	void	nonBlocking();
	int		raw() const;
	bool	isClosed() const;
	void	ensureNotClosed(void) const;

public:
	static FileDescriptor* wrapping(int fd);

};

#endif