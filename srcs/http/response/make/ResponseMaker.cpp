#include "ResponseMaker.hpp"
#include "MethodMaker.hpp"
#include "IMaker.hpp"

ResponseMaker::ResponseMaker(const ResponseMaker& other) : _req(other._req), _res(other._res), _client(other._client) {}

ResponseMaker::ResponseMaker(Request& req, Response& res, Client& client)
	: _req(req), _res(res), _client(client) {

}

ResponseMaker::~ResponseMaker(void) {

}

void ResponseMaker::setMaker(void) {
	this->_maker.push(&MethodMaker::instance());
}

void ResponseMaker::popMaker(void) {
	this->_maker.pop();
}

void ResponseMaker::executeMaker(void) {
	this->setMaker();
	IMaker *maker = this->_maker.front();
	maker->make(this->_client, this->_req, this->_res, *this);
	popMaker();
}