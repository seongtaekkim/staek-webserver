#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "HTTPStatus.hpp"
#include "../../util/Storage.hpp"
#include "StatusLine.hpp"
#include "IBody.hpp"
#include "ResponseByString.hpp"
#include "../../util/ReleaseResource.hpp"
#include "../Header.hpp"
#include "../../util/Base.hpp"
#include "../../main.hpp"

class Response {
public:
	enum State { INIT, HEADER, BODY, END };
private:
	HTTPStatus::StateType	_status;
	Header		_header;
	IBody*		_body;
	std::string _headString;
	int			_state;
	bool		_isEnd;
	std::string _cgiExtension;
	
public:
	Response(void);
	Response(const Response& other);
	Response& operator=(const Response& other);
	~Response(void);
	bool store(Storage& buffer);
	IBody* body(void) const;
	void body(IBody* body);
	void body(const std::string body);

	void status(HTTPStatus::StateType& status);
	Header& header(void);
	HTTPStatus::StateType& status(void);
	void end(void);
	bool isEnd(void) const;
	int state(void) const;
	void cgiExtension(std::string str);
	std::string cgiExtension(void) const;

};


#endif