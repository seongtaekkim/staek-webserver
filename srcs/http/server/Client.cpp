#include "Client.hpp"

int Client::_s_connCnt = 0;


Client::Client(InetAddress inetAddress, Server& server, Socket& socket)
	: _inetAddress(inetAddress), _server(server), _socket(socket) {
	Client::_s_connCnt++;
}

Client::~Client(void) {
	Client::_s_connCnt--;
}

Socket& Client::socket() const {
	return (this->_socket);
}

bool Client::recv(FileDescriptor &fd) {
	// (void)fd;
	char buf[33333]; // std::string::npos too large size
	std::cout<< "client:recv" << std::endl;
	if (static_cast<Socket&>(fd).recv(buf, 100000) <= 0)
	{
		delete this;
		return (true);
	}
	return (true);
}

// bool send(FileDescriptor& fd) {
// 	// if (!m_response.ended())
// 		// return (false);

// 	// bool finished = m_response.store(m_out);

// 	// size_t sizeBefore = m_out.size();
//     ssize_t r = 0;
// 	// // r = static_cast<Socket&>(fd).send(m_storage.data(), std::min(m_storage.length(), len), flags);

// 	// if (r > 0)
// 	// 	m_storage.erase(0, r);

//     // if ((r = static_cast<Socket&>(fd).send()) > 0)
// 	// 	std::cout << "success send" << std::endl;
//         //updateLastAction();

//     // if ((sizeBefore != 0 && r == 0) || r == -1)
//         // delete this;
//     // else if (finished && m_out.empty())

// 	// {
// 	// 	if (m_keepAlive)
// 	// 	{
// 	// 		log();
// 	// 		reset();
// 	// 	}
// 	// 	else
// 	// 		delete this;
// 	// }

// 	return (false);
// }