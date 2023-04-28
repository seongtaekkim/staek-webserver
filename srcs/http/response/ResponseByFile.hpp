#ifndef ResponseByFile_HPP
#define ResponseByFile_HPP

#include "../server/RWCallback.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../../util/Storage.hpp"
#include "../SHTTP.hpp"

class Storage;

class ResponseByFile : RWCallback {
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
	ResponseByFile(FileDescriptor& fd, std::size_t contentLength);
	virtual ~ResponseByFile(void);
	bool store(Storage& store);
	virtual bool recv(FileDescriptor& fd);
	bool isEnd(void);
};

#endif
