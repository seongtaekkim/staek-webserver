#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "HTTPState.hpp"
#include "../../util/Storage.hpp"
#include "StatusLine.hpp"
// #include "../Header.hpp"
// #include "make/ResponseMaker.hpp"

// class ResponseMaker;

class Response {
private:
	HTTPStatus::StateType	_status;
	// ResponseMaker			_maker;
	// Header _header;
	std::string				_body;
	
public:
	Response(void);
	Response(const Response& other);
	Response& operator=(const Response& other);
	~Response(void);
	bool store(Storage& buffer);
	std::string body(void) const;
	void body(std::string body);

	void status(HTTPStatus::StateType& status);
	enum State { INIT, HEADER, BODY, END };
	State _state;


};


#endif