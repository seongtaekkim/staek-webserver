#ifndef WEBSERV_HPP
#define WEBSERV_HPP

/**
 * @brief webserv 관리
 * @details http 요청/응답 처리 관리객체
 * @author seongtki
 * @date 2023.03.26
 */
class Webserv {
private:
public:
	Webserv(void);
	Webserv(const Webserv& other);
	Webserv& operator=(const Webserv& other);
	~Webserv(void);
	static void start(void);
	void stop(void);
};

#endif