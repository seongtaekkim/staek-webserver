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
	// if (res.status().get()->isError() || req.headers().get(Header::CONNECTION).equals(Header::CLOSE))
	// {
	// 	if (!(res.status().get() == HTTPStatus::PAYLOAD_TOO_LARGE))
	// 	{
	// 		//client.keepAlive(false);
	// 		res.header().connection(Header::CLOSE);
	// 	}
	// }
	std::cout <<"res.header().get(Header::TRANSFER_ENCODING) : " << res.header().get(Header::TRANSFER_ENCODING) << std::endl;
	if (!res.body() && res.header().get(Header::TRANSFER_ENCODING).length() > 0 ) {
		res.header().contentLength(0);
	}
	if (client.parser().method().compare("HEAD") == 0)
		res.body(NULL);

	// res.headers().date();
	// res.headers().server();
	std::cout <<"res.header().get(Header::TRANSFER_ENCODING) : " << res.isEnd() << std::endl;
	res.end();

	KqueueManage::instance().setEvent(client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	maker.executeMaker();
}
