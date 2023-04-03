#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "HTTPState.hpp"
// #include "make/ResponseMaker.hpp"

// class ResponseMaker;

class Response {
private:
	HTTPStatus::StateType	_status;
	// ResponseMaker			_maker;
	std::string				_body;
public:
	Response(void);
	Response(const Response& other);
	Response& operator=(const Response& other);
	~Response(void);
	void setStatus(HTTPStatus::StateType stateMap);
	bool store(std::string buffer);
	std::string body(void) const;
};


#endif