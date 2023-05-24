#include "ResponseMaker.hpp"
#include "MethodMaker.hpp"
#include "EndResponseMaker.hpp"
#include "ErrorPageMaker.hpp"
#include "DefaultPageMaker.hpp"
#include "CGIMaker.hpp"
#include "InterceptorMaker.hpp"
#include "IMaker.hpp"

ResponseMaker::ResponseMaker(const ResponseMaker& other) : _req(other._req), _res(other._res), _client(other._client) {}

ResponseMaker::ResponseMaker(Request& req, Response& res, Client& client)
	: _req(req), _res(res), _client(client) {}

ResponseMaker::~ResponseMaker(void) {}


void ResponseMaker::setMaker(void) {
	this->_maker.push(&InterceptorMaker::instance());
	this->_maker.push(&DefaultPageMaker::instance());
	this->_maker.push(&CGIMaker::instance());
	this->_maker.push(&MethodMaker::instance());
	this->_maker.push(&ErrorPageMaker::instance());
	this->_maker.push(&EndResponseMaker::instance());
}

void ResponseMaker::setLastMaker(void) {
	this->_maker.push(&ErrorPageMaker::instance());
	this->_maker.push(&EndResponseMaker::instance());
}

void ResponseMaker::popMaker(void) {
	this->_maker.pop();
}

void ResponseMaker::executeMaker(void) {
	if (!this->_maker.empty()) {
		IMaker *maker = this->_maker.front();
		popMaker();
		maker->make(this->_client, this->_req, this->_res, *this);
	}
}