#include "../../../config/block/LocationBlock.hpp"
#include "../../../config/block/ServerBlock.hpp"
#include "InterceptorMaker.hpp"
#include "../../server/Client.hpp"
#include "../../request/Request.hpp"
#include "../../parse/Parser.hpp"
#include "../../parse/PathParser.hpp"
#include "../../interceptor/HTTPFindLocation.hpp"
#include <list>
#include <string>

InterceptorMaker::InterceptorMaker(void) {}

InterceptorMaker::InterceptorMaker(const InterceptorMaker& other) {
	(void)other;
}

InterceptorMaker::~InterceptorMaker() {}

InterceptorMaker& InterceptorMaker::operator=(const InterceptorMaker& other) {
	(void)other;
	return (*this);
}

void InterceptorMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	std::list<ServerBlock *> serverList =  client.server().getServerBlocks();
	if (serverList.size() < 1) {
		res.status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
		res.end();
		return ;
	}
	req.serverBlock(*serverList.front()); // currnt only one (later for find one)
	const ServerBlock &serverBlock = *req.serverBlock();
	const std::list<LocationBlock*> locations = serverBlock.locationBlockList();
	if (locations.empty())
		return (client.maker().executeMaker());

	const std::string& path = client.parser().pathParser().path();

	HTTPFindLocation findLocation(path, locations);
	if (findLocation.parse().location()) {
		const LocationBlock &locationBlock = *findLocation.parse().location();
		req.locationBlock(locationBlock);
		if (!locationBlock.getRoot().empty()) {
			std::string path;
			if (locationBlock.getPath().c_str()[locationBlock.getPath().size() - 1] == '/') {
				if (locationBlock.getPath().size() <= req.resource().size())
					path = req.resource().substr(locationBlock.getPath().size(), std::string::npos);
				else {
					path = "";
				}	
			}
			else {
				size_t found = locationBlock.getPath().find_last_of('/');
				if (found != std::string::npos)
					path = locationBlock.getPath().substr(found, std::string::npos);
				else
					path = locationBlock.getPath();
			}
			req.resource(path);
		}
	}
	client.maker().executeMaker();
}
