#include "DefaultPageMaker.hpp"
#include "../../../file/File.hpp"
#include "../../../config/Config.hpp"
#include <string>
#include "../method/IMethod.hpp"
#include "../method/Method.hpp"

DefaultPageMaker::DefaultPageMaker(void) {}

DefaultPageMaker::DefaultPageMaker(const DefaultPageMaker& other) {
	(void)other;
}

DefaultPageMaker::~DefaultPageMaker(void) {}

DefaultPageMaker& DefaultPageMaker::operator=(const DefaultPageMaker& other) {
	(void)other;
	return (*this);
}

void DefaultPageMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {

	if (client.parser().method().size() == 0)
		return (maker.executeMaker());

	if (!(client.parser().method().compare("GET") == 0 || client.parser().method().compare("HEAD") == 0))
		return (maker.executeMaker());

	File targetFile(req.targetFile());
	if (!(targetFile.exists() && targetFile.isDir())) {
		maker.executeMaker();
		return ;
	}

	if (!req.locationBlock())
		return (maker.executeMaker());
	const LocationBlock &locationBlock = *req.locationBlock();
	if (locationBlock.getIndex().empty())
		return (maker.executeMaker());

	const std::string &indexFiles = locationBlock.getIndex();
	File anIndex(targetFile, indexFiles);
	if (anIndex.exists() && anIndex.isFile()) {
		req.resource(File(req.resource(), indexFiles).path());
		return (maker.executeMaker());
	}

	if (Config::instance().rootBlock()->ServerBlockList().empty())
		return (maker.executeMaker());

	if (Config::instance().rootBlock()->ServerBlockList().front()->getIndex().size() == 0)
		return (maker.executeMaker());

	File file(req.targetFile().path(), Config::instance().rootBlock()->ServerBlockList().front()->getIndex());

	if (file.exists() && file.isFile()) {
		req.resource(file.name());
		std::cout << "header().contentLength" << std::endl;
		res.header().contentLength(10);
	}
	maker.executeMaker();
}
