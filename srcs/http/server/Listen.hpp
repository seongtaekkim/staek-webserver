#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <iostream>


/**
 * @brief client ip, port 정보 관리
 * @details
 * @author seongtki
 * @date 2023.03.23
 */
class Listen {
private:
	std::string	_ip;
	int			_port;
	Listen(void);
	Listen(const Listen& other);
	Listen& operator=(const Listen& other);
public:
	Listen(std::string ip, int _port);
	~Listen(void) throw();
	std::string getIp() const;
	int getPort() const;
};

#endif
