#include "RWCallback.hpp"

RWCallback::~RWCallback() {}

bool RWCallback::recv(FileDescriptor& fd) {
	(void)fd;
	return (true);
}
bool RWCallback::send(FileDescriptor& fd) {
	(void)fd;
	return (true);
}