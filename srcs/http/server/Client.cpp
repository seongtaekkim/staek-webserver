#include "Client.hpp"

int Client::_s_connCnt = 0;


Client::Client(InetAddress inetAddress, Server& server, Socket& socket)
	: _inetAddress(inetAddress), _server(server), _socket(socket), _in(this->_socket), _out(this->_socket)
	, _req(), _res(), _maker(this->_req, this->_res, *this) {
	Client::_s_connCnt++;
	this->_currProgress = Client::HEADER;
}

Client::Client(const Client& other) 
	: _inetAddress(other._inetAddress), _server(other._server)
	, _socket(other._socket), _in(this->_socket), _out(this->_socket)
	, _req(other._req), _res(other._res), _maker(other._maker){}

Client::~Client(void) {
	Client::_s_connCnt--;
	// delete &this->_in;
	// delete &this->_out;
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
	Request test(this->_in.storage());

	std::cout << "< Request Line >\n";
	std::cout << test.method() << " " << test.uri() << " " << test.version() << std::endl;
	std::cout << "< Headers > \n";
	const auto& headers = test.headers();
	for (auto it = headers.cbegin(); it != headers.cend(); ++it) {
		std::cout << it->first << ": ";
		const auto& values = it->second;
		for (auto valueIt = values.cbegin(); valueIt != values.cend(); ++valueIt) {
			std::cout << *valueIt;
			if (valueIt != values.cend() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "< Body > \n";
	std::cout << test.body() << std::endl;
	std::cout << "request end ===============================" << std::endl;

	std::cout << "receive=================================================================" << std::endl;
	std::cout << this->_in.storage() << std::endl;
	std::cout << "receive=================================================================" << std::endl;
	this->progress();
	return (true);
}

bool Client::send(FileDescriptor& fd) {
	
	// response 종료 체크
	// m_out size 체크

	(void)fd;
	std::cout<< "send in in ini " << std::endl;
	std::cout << this->_in.size() << std::endl;
	if (this->_in.size() == 0)
		return (false);
    ssize_t ret = 0;
	// request, response 로직에서 생서한 응답버퍼 _out 를 send해야 함.
    // if ((ret = this->_out.send()) > 0)
    // if ((ret = this->_in.send()) > 0)
		//std::cout << "out ret : " << ret << std::endl;
 		// 시간 체크
		// std::cout << this->_res.body() << std::endl;
	// _out.store(this->_res.body());
	this->_res.store(_out);
	std::cout << "send=================================================================" << std::endl;
	std::cout << this->_out.storage() << std::endl;
	std::cout << "send=================================================================" << std::endl;
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
	this->_currProgress = Client::BODY;
	progressBody();
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
					this->_currProgress = END;
				// }

				// NIOSelector::instance().update(m_socket, NIOSelector::NONE);
				// m_filterChain.doChainingOf(FilterChain::S_BETWEEN);
				this->_currProgress = END;
				this->_res.status(HTTPStatus::STATE[HTTPStatus::OK]);
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