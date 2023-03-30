#ifndef SOCKETSTORAGE_HPP
#define SOCKETSTORAGE_HPP

#include "../../util/Storage.hpp"
#include "Socket.hpp"
#include "../../file/FileDescriptor.hpp"

class SocketStorage : public Storage {
private:
	FileDescriptor& _fd;

	SocketStorage(void);
	SocketStorage(const SocketStorage& other);
	SocketStorage& operator=(const SocketStorage& other);

public:
	static std::size_t	_s_len;
	static int			_s_flags;

public:
	virtual ~SocketStorage(void);

	SocketStorage(FileDescriptor& fd);
	ssize_t recv(void);
	ssize_t send(void);
public:
	static SocketStorage* of(Socket& socket);
};

#endif