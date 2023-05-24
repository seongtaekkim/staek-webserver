#include "ErrorPageMaker.hpp"
#include "../HTTPStatus.hpp"
#include "../../../view/Page.hpp"

ErrorPageMaker::ErrorPageMaker(void) {}

ErrorPageMaker::ErrorPageMaker(const ErrorPageMaker& other) {
	(void)other;
}

ErrorPageMaker::~ErrorPageMaker(void) {}

ErrorPageMaker& ErrorPageMaker::operator=(const ErrorPageMaker &other) {
	(void)other;
	return (*this);
}

void ErrorPageMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	(void)client;
	(void)req;

	const HTTPStatus::StateType state = res.status();
	if (state.first / 100 != 4 && state.first / 100 != 5) {
		if (state.first != 405)
			maker.executeMaker();
		return ;
	}
	res.body(Page::instance().resolve(state));
	maker.executeMaker();
}
