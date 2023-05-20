#ifndef RESPONSEBYCGI_HPP
#define RESPONSEBYCGI_HPP

#include "../../util/Storage.hpp"
#include "../server/RWCallback.hpp"
#include "IBody.hpp"

class CGITask;
class Client;

class ResponseByCGI : public RWCallback, public IBody {
private:
	Client&		_client;
	CGITask&	_task;
	bool		_isEnd;

private:
	ResponseByCGI(void);
	ResponseByCGI(const ResponseByCGI& other);
	ResponseByCGI& operator=(const ResponseByCGI& other);

public:
	ResponseByCGI(Client& client, CGITask& task);
	virtual ~ResponseByCGI(void);
	bool isSelfManaged(void) const;
	virtual bool store(Storage& buffer);
	virtual bool isEnd(void);
};

#endif

