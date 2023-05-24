#include "CGI.hpp"
#include "../../exception/Exception.hpp"
#include "CGITask.hpp"
#include "../response/method/Method.hpp"
#include "../response/method/IMethod.hpp"
#include "../response/HTTPStatus.hpp"
#include "../response/make/ResponseMaker.hpp"
#include "../response/HTTPStatus.hpp"
#include "../server/Client.hpp"
#include "../request/Request.hpp"
#include "../response/ResponseByCGI.hpp"
#include "../response/Response.hpp"
#include "../server/Socket.hpp"
#include <sys/types.h>
#include "../../util/Base.hpp"
#include "../SHTTP.hpp"
#include <iostream>
#include <string>

class Parser;
class ResponseByCGI;

CGITask::CGITask(Client& client, CGI& cgi) :
		_client(client), _cgi(cgi),
		wroteBodyUpTo(), _running(true) {
	IMethod* method = Method::METHOD[client.parser().method()];
	KqueueManage::instance().create(this->_cgi.in(), *this, _client.server().getSocket()->getFd());
	if (method->getHasBody()) {
		KqueueManage::instance().setEvent(_cgi.in().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	else
		this->_cgi.in().close();
		
	KqueueManage::instance().create(this->_cgi.out(), *this, _client.server().getSocket()->getFd());
	KqueueManage::instance().setEvent(_cgi.out().getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

CGITask::~CGITask(void) {
	this->_cgi.kill();
	KqueueManage::instance().delEvent(_cgi.in().getFd());
	KqueueManage::instance().delEvent(_cgi.out().getFd());
	delete &_cgi;
}

bool CGITask::running() {
	return (_running);
}

bool CGITask::send(FileDescriptor& fd) {

	if (_cgi.in().isClosed())
		return (true);
	if (wroteBodyUpTo == _client.body().length()) {
		_cgi.in().close();	
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	ssize_t wrote = fd.write(_client.body().c_str() + wroteBodyUpTo, _client.body().length() - wroteBodyUpTo);

	if (wrote <= 0) {
		this->_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	wroteBodyUpTo += wrote;
	if (wroteBodyUpTo == _client.body().length()) {
		_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}
	return (false);
}

bool CGITask::recv(FileDescriptor& fd) {
	(void)fd;

	std::string ret = _cgi.out().readString();
	_cgi.out().store(ret);
	if (ret.empty()) {
		_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		_client.maker().executeMaker();
		KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		return (true);
	}

	Parser parser(_client);
    parser.hState(Parser::FIELD);
	if (parser.state() != Parser::HEND) {
		char c;
		try {
			while (_cgi.out().getC(c)) {
				_cgi.out().next();
				parser.headerParse(c);
				if (parser.hState() == Parser::HEND) {
					parser.header().get(Header::STATUS);
					_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);

					break;
				}
			}

			this->_client.response().header().contentLength(_cgi.out().storage().size());
			this->_client.response().body(new ResponseByCGI(this->_client, *this));
			_client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
			_client.maker().executeMaker();
			KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			return (false);
		} catch (Exception &exception) {
			this->_client.response().status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
			this->_client.maker().executeMaker();

			KqueueManage::instance().setEvent(this->_client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			return (true);
		}
	}

	if (_cgi.out().isReadCompleted()) {
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}
	return (false);
}

bool CGITask::isDone() {
	return (_cgi.out().isReadCompleted());
}

bool CGITask::hasReadHeaders() {
	return (_client.parser().hState() != Parser::HEND);
}

FileDescriptor& CGITask::out() {
	return (_cgi.out());
}

bool CGITask::timeoutTouch() {
	if (this->_running) {
		this->_running = this->_cgi.running();
		return (true);
	}
	return (false);
}
