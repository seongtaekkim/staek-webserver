#include "Client.hpp"

int Client::_s_connCnt = 0;


Client::Client(InetAddress inetAddress, Server& server, Socket& socket)
	: _inetAddress(inetAddress), _server(server), _socket(socket), _in(this->_socket), _out(this->_socket)
	, _req(), _res(), _maker(this->_req, this->_res, *this), _parser(), _pathParser() {
	Client::_s_connCnt++;
	this->_currProgress = Client::HEADER;
	KqueueManage::instance().create(this->_socket, *this);
}

Client::Client(const Client& other) 
	: _inetAddress(other._inetAddress), _server(other._server)
	, _socket(other._socket), _in(this->_socket), _out(this->_socket)
	, _req(other._req), _res(other._res), _maker(other._maker){}

Client::~Client(void) {
	Client::_s_connCnt--;
	// delete &this->_in;
	// delete &this->_out;
	std::cout << "client disconnect !! " << this->_socket.getFd() << std::endl;
	this->_server.disconnect(*this);
	// delete &this->_socket;
}

Socket& Client::socket() const {
	return (this->_socket);
}

// recv 0 == client에서 접속종료
bool Client::recv(FileDescriptor &fd) {
	(void)fd;
	if (this->_in.recv() <= 0) {
		delete this;
		return (false);
	}

	std::cout << "request start ===============================" << std::endl;
	// std::cout << this->_in.storage() << std::endl;

	// Request test(this->_in.storage());

	// std::cout << "< Request Line >	\n";
	// std::cout << test.method() << " " << test.uri() << " " << test.version() << std::endl;
	// std::cout << "< Headers > \n";
	// const auto& headers = test.headers();
	// for (auto it = headers.cbegin(); it != headers.cend(); ++it) {
	// 	std::cout << it->first << ": ";
	// 	const auto& values = it->second;
	// 	for (auto valueIt = values.cbegin(); valueIt != values.cend(); ++valueIt) {
	// 		std::cout << *valueIt;
	// 		if (valueIt != values.cend() - 1) {
	// 			std::cout << ", ";
	// 		}
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << "< Body > \n";
	// std::cout << test.body() << std::endl;
	std::cout << "request end ===============================" << std::endl;
	std::cout << "receive=================================================================" << std::endl;
	// std::cout << this->_in.storage() << std::endl;
	std::cout << "receive end =================================================================" << std::endl;
	this->progress();
	std::cout << "progress end !!!!!!!" << std::endl;
	return (true);
}

bool Client::send(FileDescriptor& fd) {
	
	// response 종료 체크
	// m_out size 체크

	(void)fd;
	std::cout<< "send in in ini " << std::endl;

	if (this->_currProgress != Client::END)
		return (false);
    ssize_t ret = 0;
	// request, response 로직에서 생서한 응답버퍼 _out 를 send해야 함.
    // if ((ret = this->_out.send()) > 0)
    // if ((ret = this->_in.send()) > 0)
		//std::cout << "out ret : " << ret << std::endl;
 		// 시간 체크
		// std::cout << this->_res.body() << std::endl;
	// _out.store(this->_res.body());
	std::cout << "send=================================================================" << std::endl;
	this->_res.store(_out);
	// std::cout << this->_out.storage() << std::endl;
	std::cout << "send end ===============================================" << std::endl;
	ret = this->_out.send();
	if (ret == -1)
		delete this;
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
		std::cout << c ;
		this->_in.next();
		//bool catched = true;
		try {
			_parser.parse(c);
			// if (m_parser.state() == HTTPRequestParser::S_END)
			// {
			// 	// std::cout << "******" << std::endl;
			// 	m_request = HTTPRequest(m_parser.version(), m_parser.url(), m_parser.headerFields());
			// 	m_filterChain.doChainingOf(FilterChain::S_BEFORE);

			// 	if (m_request.method().absent() && m_response.ended())
			// 	{
			// 		m_filterChain.doChainingOf(FilterChain::S_AFTER);
			// 		m_state = S_END;
			// 		return (true);
			// 	}
				

			// }
			URL url = URL().builder().appendPath(_parser.pathParser().path()).build();
			_req = Request(StatusLine(), url);
			if (this->_parser.state() == Parser::END) {
				// if (Method::METHOD[this->parser().method()]->getHasBody() == true) {
				if (1 == 2) {
					_parser.state(Parser::STATE::BODY);
					this->_currProgress = Client::BODY;
					_parser.parse(0);
					if (_parser.state() != Parser::END)
						return (progressBody());
				} else {
					this->_maker.executeMaker();
					this->_res.status(HTTPStatus::STATE[HTTPStatus::OK]);
				}
				break;
			}
			// catched = false;
		} catch (Exception &exception) {
			std::cerr << "Failed to process header: " << exception.message() << std::endl;
			this->_res.status(HTTPStatus::STATE[HTTPStatus::BAD_REQUEST]);
		}

		// if (catched)
		// {
		// 	NIOSelector::instance().update(m_socket, NIOSelector::NONE);
		// 	m_filterChain.doChainingOf(FilterChain::S_AFTER);
		// 	m_state = S_END;

		// 	break;
		// }
	}

	return (true);
}

bool Client::progressBody(void) {
	if (!this->_in.storage().empty()) {
		try {
			// m_parser.consume(0);

			// if (m_parser.state() == HTTPRequestParser::S_END)
			// {
				// if (m_response.ended())
				// {
					this->_maker.executeMaker();
					// this->_maker .doChainingOf(FilterChain::S_AFTER);
				// }

				// NIOSelector::instance().update(m_socket, NIOSelector::NONE);
				// m_filterChain.doChainingOf(FilterChain::S_BETWEEN);
				this->_res.status(HTTPStatus::STATE[HTTPStatus::OK]);
				// KqueueManage::instance().setEvent(this->_socket.getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
				return (true);
				// }
		} catch (Exception &exception) {
			this->_res.status(HTTPStatus::STATE[HTTPStatus::BAD_REQUEST]);
			this->_maker.executeMaker();
			this->_currProgress = Client::END;
		}
	}
	return (false);
}


int Client::state(void) {

	if (this->_res.body() && this->_res.body()->isEnd() == true)
		this->_currProgress = Client::END;


	return (this->_currProgress);
}

Parser Client::parser(void) {
	return (this->_parser);
}
