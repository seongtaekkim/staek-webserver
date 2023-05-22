#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <list>

class Server;
class Logger;

/**
 * @brief webserv 관리
 * @details http 요청/응답 처리 관리객체
 * @author seongtki
 * @date 2023.03.26
 */
class Webserv {
public:
	typedef std::list<Server*> ServerList;
public:
	static Logger& logger;
private:
	ServerList	_servers;
	bool		_isRun;
	bool		_isStop;
private:
	Webserv(void);
	Webserv(const ServerList& server);
	Webserv(const Webserv& other);
	Webserv& operator=(const Webserv& other);
public:
	virtual ~Webserv(void);
	static Webserv* create(void);
	void run(void);
	void stop(void);
};

#endif