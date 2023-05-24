#include "Client.hpp"
#include "../response/method/Method.hpp"
#include "../../iom/KqueueManage.hpp"
#include "../exception/UnsupportedVersionException.hpp"
#include "../exception/TooBigHeaderException.hpp"
#include "../exception/PayloadTooBigException.hpp"

int Client::_s_connCnt = 0;


Client::Client(InetAddress inetAddress, Server& server, Socket& socket)
	: _inetAddress(inetAddress), _server(server), _socket(socket), _in(this->_socket), _out(this->_socket)
	, _req(), _res(), _maker(this->_req, this->_res, *this), _parser(*this), _pathParser(), _putTask(), _cgiTask() {
	Client::_s_connCnt++;
	this->_currProgress = Client::HEADER;
	KqueueManage::instance().create(this->_socket, *this, _server.getSocket()->getFd());
	updateTime();
}

Client::Client(const Client& other) 
	: _inetAddress(other._inetAddress), _server(other._server)
	, _socket(other._socket), _in(this->_socket), _out(this->_socket)
	, _req(other._req), _res(other._res), _maker(other._maker), _parser(other._parser) {}

Client::~Client(void) {
	Client::_s_connCnt--;
	if (this->_putTask)
		ReleaseResource::pointer(this->_putTask);
	if (this->_cgiTask)
		ReleaseResource::pointer(this->_cgiTask);
	this->_server.disconnect(*this);
	delete &this->_socket;
}

Socket& Client::socket() const {
	return (this->_socket);
}

bool Client::recv(FileDescriptor &fd) {
	(void)fd;
	if (this->_in.recv() <= 0) {
		delete this;
		return (false);
	}

	this->progress();
	updateTime();
	return (true);
}

bool Client::send(FileDescriptor& fd) {

	(void)fd;

	if (this->_currProgress == Client::END)
		return (false);
	if (this->_res.isEnd() != true)
		return (false);
	this->_res.store(_out);
    ssize_t ret = 0;
	ret = this->_out.send();
	if (ret > 0)
		updateTime();
	this->_currProgress = Client::END;
	_out.clear();
	_in.clear();
	return (true);
}

bool Client::progress(void) {

	switch (this->_currProgress) {
		case Client::HEADER:
			return (progressHead());

		case Client::BODY:
			return (progressBody());

		case Client::END:
			return (true);
	}
	return (false);
}


bool Client::progressHead(void) {

	char c;
	while (this->_in.getC(c)) {
		this->_in.next();
		bool exitParse = true;
		try {
			_parser.parse(c);

			if (this->_parser.state() == Parser::END) {
				URL url = URL().builder().appendPath(_parser.pathParser().path()).build();
				_req = Request(_parser.header() ,StatusLine(), url);
				if (!Method::METHOD[this->parser().method()]) {
					this->_res.header().contentLength(0);
					this->_res.status(HTTPStatus::STATE[HTTPStatus::METHOD_NOT_ALLOWED]);
					this->_maker.setLastMaker();
					this->_maker.executeMaker();
				} else if (Method::METHOD[this->parser().method()]->getHasBody() == true) {
					_parser.state(Parser::BODY);
					this->_currProgress = Client::BODY;
					_parser.parse(0);
					if (_parser.state() != Parser::END)
						return (progressBody());
					else {
						this->_maker.setMaker();
						this->_maker.executeMaker();
					}
				} else {
					this->_maker.setMaker();
					this->_maker.executeMaker();
				}
				break;
			}
			exitParse = false;

		} catch (UnsupportedVersionException& exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::HTTP_VERSION_NOT_SUPPORTED]);
		} catch (TooBigHeaderException& exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::REQUEST_HEADER_FIELDS_TOO_LARGE]);
		} catch (PayloadTooBigException& exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::PAYLOAD_TOO_LARGE]);
		} catch (Exception &exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::BAD_REQUEST]);
		}
		if (exitParse == true) {
			this->_maker.setLastMaker();
			this->_maker.executeMaker();
			break;
		}
	}

	return (true);
}

bool Client::progressBody(void) {
	
	if (!this->_in.storage().empty()) {
		try {
			_parser.parse(0);
			this->_maker.setMaker();
			this->_maker.executeMaker();
			if (this->_res.status().second.empty())
				this->_res.status(HTTPStatus::STATE[HTTPStatus::OK]);
			return (true);
		} catch (PayloadTooBigException& exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::PAYLOAD_TOO_LARGE]);
		} catch (Exception &exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::BAD_REQUEST]);
			this->_maker.setMaker();
			this->_maker.executeMaker();
		}
	}
	return (false);
}


int Client::state(void) {

	if (this->_res.body() && this->_res.body()->isEnd() == true)
		this->_currProgress = Client::END;

	return (this->_currProgress);
}

Parser& Client::parser(void) {
	return (this->_parser);
}

Response& Client::response(void) {
	return (this->_res);
}

ResponseMaker& Client::maker(void) {
	return (this->_maker);
}

void Client::fileWrite(PutTask &task) {
	if (_putTask)
		delete _putTask;
	_putTask = &task;
}

void Client::cgiWrite(CGITask& task) {
	if (_cgiTask)
		delete _cgiTask;
	_cgiTask = &task;
}

PutTask* Client::fileWrite(void) {
	return (this->_putTask);
}

CGITask* Client::cgiWrite(void) {
	return (this->_cgiTask);
}

std::string& Client::body(void) {
	return (this->_body);
}

SocketStorage& Client::in(void) {
	return (this->_in);
}

SocketStorage& Client::out(void) {
	return (this->_out);
}

void Client::end() {
	this->_currProgress = Client::END;
}

Request& Client::request(void) {
	return (this->_req);
}

Server& Client::server(void) {
	return (this->_server);
}

InetAddress Client::inetAddress(void) const {
	return (this->_inetAddress);
}

void Client::updateTime(void) {
	unsigned long time = Time::currentSecond();
	if (time)
		this->_lastTime = time;
}

unsigned long Client::lastTime(void) const {
	return (this->_lastTime);
}

void Client::deny(Client& client) {
	client.response().status(HTTPStatus::STATE[HTTPStatus::SERVICE_UNAVAILABLE]);
	client.maker().setLastMaker();
	client.maker().executeMaker();
	KqueueManage::instance().setEvent(client.socket().getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
}

unsigned long Client::clientMaxBodySize(const ServerBlock* serverBlock, const LocationBlock* locationBlock) {
	if (locationBlock && locationBlock->getClientMaxBodySize() > 0)
		return (locationBlock->getClientMaxBodySize());
	if (serverBlock && serverBlock->getClientMaxBodySize() > 0)
		return (serverBlock->getClientMaxBodySize());
	return (SHTTP::DEFAULT_MAX_BODY_SIZE);
}