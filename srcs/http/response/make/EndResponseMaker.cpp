#include "EndResponseMaker.hpp"

EndResponseMaker::EndResponseMaker(void) {}

EndResponseMaker::EndResponseMaker(const EndResponseMaker& other) {
	(void)other;
}

EndResponseMaker::~EndResponseMaker(void) {}

EndResponseMaker& EndResponseMaker::operator=(const EndResponseMaker& other) {
	(void)other;
	return (*this);
}

void EndResponseMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	(void)req;
	if (!res.body() && res.header().get(Header::TRANSFER_ENCODING).length() > 0 ) {
		res.header().contentLength(0);
	}
	if (client.parser().method().compare("HEAD") == 0)
		res.body(NULL);

	res.end();
	KqueueManage::instance().setEvent(client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	maker.executeMaker();
}
