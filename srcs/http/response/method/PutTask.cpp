#include "PutTask.hpp"

PutTask::PutTask(Client &client, FileDescriptor &fd, bool justCreated) :
		_client(client), _fileDescriptor(fd), _storedCount(0), _justCreated(justCreated) {
	KqueueManage::instance().create(fd, *this, _client.server().getSocket()->getFd());
	KqueueManage::instance().setEvent(fd.getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

PutTask::~PutTask() {
	KqueueManage::instance().delEvent(this->_fileDescriptor.getFd());
	delete &_fileDescriptor;
}

bool PutTask::send(FileDescriptor& fd) {
	ssize_t stored = fd.write(_client.body().c_str() + _storedCount, _client.body().length() - _storedCount);
	
	if (stored == -1) {
		_storedCount = -1;	
		this->~PutTask();
		_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		_client.maker().executeMaker();
		return (true);
	}
	else if (stored == 0 && _storedCount == static_cast<ssize_t>(_client.body().length())) {
		if (_justCreated)
			_client.response().status(HTTPStatus::STATE[HTTPStatus::CREATED]);
		else
			_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
		
		_client.maker().executeMaker();
		_client.response().end();
		return (true);
	}
	else
		_storedCount += stored;

	return (false);
}
