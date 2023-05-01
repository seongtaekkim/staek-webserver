#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "HTTPState.hpp"
#include "../../util/Storage.hpp"
#include "StatusLine.hpp"
#include "IBody.hpp"
#include "ResponseByString.hpp"
#include "../../util/ReleaseResource.hpp"


// #include "../Header.hpp"
// #include "make/ResponseMaker.hpp"

// class ResponseMaker;

class Response {
private:
	HTTPStatus::StateType	_status;
	// ResponseMaker			_maker;
	// Header _header;
	IBody*		_body;
	std::string _headString;
	
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
	HTTPStatus::StateType& status(void);
	enum State { INIT, HEADER, BODY, END };
	State _state;


};


#endif