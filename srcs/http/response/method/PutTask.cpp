#include "PutTask.hpp"

PutTask::PutTask(Client &client, FileDescriptor &fd, bool justCreated) :
		m_client(client),
		m_fileDescriptor(fd),
		m_storedCount(0),
		m_justCreated(justCreated) {
	KqueueManage::instance().create(fd, *this);
	KqueueManage::instance().setEvent(fd.getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

PutTask::~PutTask() {
	std::cout << "PutTask::~PutTask : " << this->m_fileDescriptor.getFd() << std::endl;
	KqueueManage::instance().delEvent(this->m_fileDescriptor.getFd());
	delete &m_fileDescriptor;
}

bool PutTask::send(FileDescriptor& fd) {
	ssize_t stored = fd.write(m_client.body().c_str() + m_storedCount, m_client.body().length() - m_storedCount);
	std::cout << "PutTask::writable : " << stored << " " << m_storedCount << " " << static_cast<ssize_t>(m_client.body().length()) << std::endl;
	
	if (stored == -1) {
		m_storedCount = -1;	
		this->~PutTask();
		m_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		m_client.maker().executeMaker();
		return (true);
	}
	else if (stored == 0 && m_storedCount == static_cast<ssize_t>(m_client.body().length()))
	{
			std::cout << "???PutTask::writable : " << stored << " " << m_storedCount << " " << static_cast<ssize_t>(m_client.body().length()) << std::endl;
		if (m_justCreated)
			m_client.response().status(HTTPStatus::STATE[HTTPStatus::CREATED]);
		else
			m_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
		
		m_client.maker().executeMaker();
		// m_client.end();
		m_client.response().end();


		return (true);
	}
	else
		m_storedCount += stored;

	return (false);
}
