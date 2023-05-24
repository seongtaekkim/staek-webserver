#ifndef RESPONSEBYFILE_HPP
#define RESPONSEBYFILE_HPP

#include "IBody.hpp"
#include "../server/RWCallback.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../SHTTP.hpp"

class ResponseByFile : public RWCallback, public IBody {
private:
	FileDescriptor&	_fd;
	std::size_t		_contentLength;
	std::size_t		_store;
	bool			_isEnd;

private:
	ResponseByFile(void);
	ResponseByFile(const ResponseByFile& other);
	ResponseByFile& operator=(const ResponseByFile& other);

public:
	ResponseByFile(FileDescriptor& fd, std::size_t contentLength, int serverFd);
	virtual ~ResponseByFile(void);
	virtual bool store(Storage& store);
	virtual bool recv(FileDescriptor& fd);
	virtual bool isEnd(void);
};

#endif
