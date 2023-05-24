#include "MethodMaker.hpp"
#include "../../../exception/Exception.hpp"
#include "../HTTPStatus.hpp"
#include "../Response.hpp"
#include "../../request/Request.hpp"
#include "../../server/Client.hpp"
#include "../method/IMethod.hpp"
#include <iostream>
#include <string>
#include "../method/Method.hpp"


MethodMaker::MethodMaker() {}
MethodMaker::~MethodMaker() {}

std::string MethodMaker::getAllowMethod(Request& req) const {
	const LocationBlock* location = req.locationBlock();
	if (location && !location->getLimitExcept().empty()) {
		return (location->getLimitExcept());
	}
	return ("");
}

unsigned long MethodMaker::clientMaxBodySize(const ServerBlock* serverBlock, const LocationBlock* locationBlock) {
	if (locationBlock && locationBlock->getClientMaxBodySize() > 0)
		return (locationBlock->getClientMaxBodySize());
	if (serverBlock && serverBlock->getClientMaxBodySize() > 0)
		return (serverBlock->getClientMaxBodySize());
	return (SHTTP::DEFAULT_MAX_BODY_SIZE);
}

void MethodMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	try {
		IMethod* method = Method::METHOD[client.parser().method()];
	
		if (method) {
			
			if (method->getHasBody()) {
				client.parser().clientMaxBodySize(clientMaxBodySize(req.serverBlock(), req.locationBlock()));
				if (client.body().size() > client.parser().clientMaxBodySize()) {
					res.status(HTTPStatus::STATE[HTTPStatus::PAYLOAD_TOO_LARGE]);
					maker.executeMaker();
				}
			}
			
			std::string allow = getAllowMethod(req);
			if (allow.empty()) {
				if (method->doMethod(req, res, client))
				return (maker.executeMaker());
			}
			if (client.parser().method().compare(allow) == 0) {
				if (method->doMethod(req, res, client))
					return (maker.executeMaker());
			}
		}
		res.header().allow(getAllowMethod(req));
		res.status(HTTPStatus::STATE[HTTPStatus::METHOD_NOT_ALLOWED]);
		maker.executeMaker();
	} catch (Exception& exception) {
		res.status(HTTPStatus::STATE[HTTPStatus::INTERNAL_SERVER_ERROR]);
		maker.executeMaker();
	}
}
