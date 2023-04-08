#include "MethodMaker.hpp"
#include "../../../exception/Exception.hpp"
#include "../HTTPState.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"
#include "../../server/Client.hpp"
#include "../method/IMethod.hpp"
#include <iostream>
#include <string>

#include "../method/Method.hpp"


MethodMaker::MethodMaker() {}
MethodMaker::~MethodMaker() {}

void MethodMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	// if (res.status())
		// return (maker.nextMaker(););

	try {
		// 임시로 GET 으로 세ㅣㅇrequest 에서 method를 받아 와야함. 
		IMethod* method = Method::METHOD[Method::GET];
		method->doMethod(req, res, client);
		std::cout << "<MethodMaker::make> in do method !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		
		// maker.nextMaker();
	} catch (Exception &exception) {
		// Failed to do method
		res.setStatus(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		//maker.nextMaker();
	}
}