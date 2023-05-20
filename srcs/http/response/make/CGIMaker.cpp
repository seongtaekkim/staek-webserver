#include "CGIMaker.hpp"
#include "../../../config/Config.hpp"
#include "../../../config/block/RootBlock.hpp"
#include "../../../config/block/ServerBlock.hpp"
#include "../../../config/block/LocationBlock.hpp"
#include "../../../exception/Exception.hpp"
#include "../../cgi/CGI.hpp"
#include "../../cgi/CGITask.hpp"
#include "../HTTPState.hpp"
#include "../../server/Client.hpp"
#include "../../request/Request.hpp"
#include "../Response.hpp"
#include "../../../file/File.hpp"
#include "../../../util/SEnvironment.hpp"
#include <iostream>
#include <string>

CGIMaker::CGIMaker(void) {	std::cout << "CGIMaker::make : " << std::endl;
}

CGIMaker::CGIMaker(const CGIMaker& other) {
	(void)other;
}

CGIMaker::~CGIMaker(void) {}

CGIMaker& CGIMaker::operator=(const CGIMaker& other) {
	(void)other;
	return (*this);
}

void CGIMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {

	std::cout << "CGIMaker::mak2e : " << std::endl;
	
	if (!req.serverBlock())
		return (client.maker().executeMaker());
	std::cout << "CGIMaker::mak3e : " << std::endl;

	if (req.serverBlock()->getCgi().first.empty())
		return (client.maker().executeMaker());
		std::cout << "CGIMaker::mak4e : " << req.resource() << std::endl;

	std::string extension;
	File f(req.resource());
	std::cout << "CGIMaker::mak44e : " << req.resource()  << std::endl;
	std::cout << "CGIMaker::mak44e : " << f.getExtension()  << std::endl;
	std::cout << "CGIMaker::mak44e : " <<  f.path() << std::endl;
	std::cout << "CGIMaker::mak44e : " <<  req.serverBlock()->getCgi().first << std::endl;
	if ((extension = f.getExtension()).empty())
		return (client.maker().executeMaker());
	if (extension.compare(req.serverBlock()->getCgi().first) != 0)
		return (client.maker().executeMaker());
	std::cout << "CGIMaker::mak555e : " << std::endl;

	const ServerBlock::CgiType& cgiType = Config::instance().rootBlock()->ServerBlockList().front()->getCgi();
	// const CGIBlock &cgiBlock = Config::instance().rootBlock().getCGI(locationBlock.cgi().get());

	// if (!cgiType.hasExtension(extension))
		// return (client.maker().executeMaker());

	// if (!cgiBlock.handleNotFound().orElse(false) && !req.targetFile().exists())
	// {
	// 	client.response().status(HTTPStatus::STATE[HTTPStatus::NOT_FOUND]);
	// 	return (client.maker().executeMaker());
	// }

	// File cgiFile(cgiType.second);
	
	File cgiFile(req.root(), cgiType.second);
	File targetFile(req.targetFile());
	std::cout << "CGIMaker::mak5e :" << "|" << targetFile.path() <<"|" << cgiFile.path() <<  std::endl;

	if (!cgiFile.exists() || !cgiFile.isFile() || !cgiFile.isExecutable()) {
				std::cout << "CGIMaker::mak5e error :" << "|" <<cgiFile.exists() <<"|" << std::endl;

		client.response().status(HTTPStatus::STATE[HTTPStatus::BAD_GATEWAY]);
		return (client.maker().executeMaker());
	}
	std::cout << "CGIMaker::mak3e : " << std::endl;

	try {
		client.cgiWrite(*CGI::execute(client, cgiType, SEnvironment::getEnv()));
		client.response().status(HTTPStatus::STATE[HTTPStatus::OK]);
	}
	catch (Exception& exception) {
		std::cout << "an error occurred while executing CGI :" << "|" <<cgiFile.exists() <<"|" << std::endl;

		//LOG.debug() << "An error occurred while executing CGI: " << exception.message() << std::endl;
		client.response().status(HTTPStatus::STATE[HTTPStatus::BAD_GATEWAY]);
		return (client.maker().executeMaker());
	}
}
