#include "SocketStorage.hpp"

std::size_t	SocketStorage::_s_len = 2 << 10;
int			SocketStorage::_s_flags = 0;
	
SocketStorage::SocketStorage(FileDescriptor& fd) : _fd(fd) {}
SocketStorage::~SocketStorage(void) {
	std::cout << "delete SocketStorage::~SocketStorage " << std::endl;
}

SocketStorage* SocketStorage::of(Socket& socket) {
	return (new SocketStorage(socket));
}

ssize_t SocketStorage::recv() {

	char buf[SocketStorage::_s_len];
	ssize_t ret = static_cast<Socket&>(this->_fd).recv(buf, SocketStorage::_s_len , SocketStorage::_s_flags);
	if (ret >= 0)
		this->store(buf, ret);

	return (ret);
}

ssize_t SocketStorage::send() {
	ssize_t ret = static_cast<Socket&>(this->_fd).send(this->storage().data(), SocketStorage::_s_len, SocketStorage::_s_flags);
	if (ret > 0)
		this->storage().erase(0, ret);
	return (ret);
}