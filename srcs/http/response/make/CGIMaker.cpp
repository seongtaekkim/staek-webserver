#include "CGIMaker.hpp"
#include "../../../config/Config.hpp"
#include "../../../config/block/RootBlock.hpp"
#include "../../../config/block/ServerBlock.hpp"
#include "../../../config/block/LocationBlock.hpp"
#include "../../../exception/Exception.hpp"
#include "../../cgi/CGI.hpp"
#include "../../cgi/CGITask.hpp"
#include "../HTTPStatus.hpp"
#include "../../server/Client.hpp"
#include "../../request/Request.hpp"
#include "../Response.hpp"
#include "../../../file/File.hpp"
#include "../../../util/SEnvironment.hpp"
#include <iostream>
#include <string>

CGIMaker::CGIMaker(void) {}

CGIMaker::CGIMaker(const CGIMaker& other) {
	(void)other;
}

CGIMaker::~CGIMaker(void) {}

CGIMaker& CGIMaker::operator=(const CGIMaker& other) {
	(void)other;
	return (*this);
}

void CGIMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	if (!req.serverBlock())
		return (maker.executeMaker());

	if (req.serverBlock()->getCgi().first.empty())
		return (maker.executeMaker());

	std::string extension;
	File f(req.resource());
	if ((extension = f.getExtension()).empty())
		return (maker.executeMaker());
	if (extension.compare(req.serverBlock()->getCgi().first) != 0)
		return (maker.executeMaker());

	const ServerBlock::CgiType& cgiType = req.serverBlock()->getCgi();
	
	File cgiFile(req.root(), cgiType.second);
	File targetFile(req.targetFile());

	if (!cgiFile.exists() || !cgiFile.isFile() || !cgiFile.isExecutable()) {
		client.response().status(HTTPStatus::STATE[HTTPStatus::BAD_GATEWAY]);
		return (maker.executeMaker());
	}

	try {
		res.cgiExtension(cgiType.first);
		client.cgiWrite(*CGI::execute(client, cgiType, SEnvironment::getEnv()));
		client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
	}
	catch (Exception& exception) {
		client.response().status(HTTPStatus::STATE[HTTPStatus::BAD_GATEWAY]);
		return (maker.executeMaker());
	}
}
