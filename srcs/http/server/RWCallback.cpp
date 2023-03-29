#include "RWCallback.hpp"

RWCallback::~RWCallback() {}

bool RWCallback::recv(FileDescriptor &fd) {
	return (true);
}
bool RWCallback::send(FileDescriptor &fd) {
	return (true);
}