#ifndef PUTTASK_HPP
#define PUTTASK_HPP

#include "../../../file/FileDescriptor.hpp"
#include "../../server/RWCallback.hpp"
#include "../../server/Client.hpp"
#include "../HTTPState.hpp"
#include "../Response.hpp"
#include "../make/ResponseMaker.hpp"
#include <stddef.h>
#include <string>


class Client;
class Request;

class PutTask : public RWCallback {
	private:
		Client& m_client;
		FileDescriptor &m_fileDescriptor;
		ssize_t m_storedCount;
		bool m_justCreated;

	private:
		PutTask(void);
		PutTask(const PutTask &other);
		PutTask& operator=(const PutTask &other);

	public:
		PutTask(Client &client, FileDescriptor &fd, bool justCreated);

		virtual ~PutTask(void);

		virtual bool send(FileDescriptor& fd);
};

#endif
