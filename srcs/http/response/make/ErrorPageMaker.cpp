#include "ErrorPageMaker.hpp"

// #include <buffer/impl/FileDescriptorBuffer.hpp>
// #include <config/block/container/CustomErrorMap.hpp>
// #include <config/block/ServerBlock.hpp>
// #include <exception/Exception.hpp>
// #include <http/enums/HTTPStatus.hpp>
// #include <http/filter/FilterChain.hpp>
// #include <http/filter/impl/after/ErrorPageMaker.hpp>
// #include <http/page/DefaultPages.hpp>
// #include <http/request/HTTPRequest.hpp>
// #include <http/response/body/impl/FileResponseBody.hpp>
// #include <http/response/HTTPResponse.hpp>
// #include <io/File.hpp>
// #include <io/FileDescriptor.hpp>
// #include <log/Logger.hpp>
// #include <log/LoggerFactory.hpp>
// #include <sys/fcntl.h>
// #include <util/helper/DeleteHelper.hpp>
// #include <util/Macros.hpp>
// #include <util/Optional.hpp>
// #include <iostream>
// #include <string>
// #include <sys/stat.h>

#include "../HTTPState.hpp"
#include "../../../view/Page.hpp"
// #include "../../../config/Config.hpp"

ErrorPageMaker::ErrorPageMaker(void) {}

ErrorPageMaker::ErrorPageMaker(const ErrorPageMaker& other)
{
	(void)other;
}

ErrorPageMaker::~ErrorPageMaker(void) {}

ErrorPageMaker& ErrorPageMaker::operator=(const ErrorPageMaker &other) {
	(void)other;
	return (*this);
}

void ErrorPageMaker::make(Client& client, Request& req, Response& res, ResponseMaker& maker) {
	// if (!response.status().present())
	// 	return (next());

	const HTTPStatus::StateType state = res.status();
	if (state.first / 100 != 4 && state.first / 100 != 5) {
		maker.executeMaker();
		return ;
	}

	// if (response.body() && response.body()->isSelfManaged())
	// 	return (next());

	bool success = false;
	// if (request.serverBlock().present())
	// {
	// 	const ServerBlock &serverBlock = *request.serverBlock().get();

	// 	if (serverBlock.errors().present())
	// 	{
	// 		const CustomErrorMap &errorMap = serverBlock.errors().get();
	// 		if (errorMap.has(status))
	// 		{
	// 			File errorFile(request.root(), errorMap.get(status));

	// 			FileDescriptor *fd = NULL;
	// 			FileDescriptorBuffer *fdBuffer = NULL;
	// 			try
	// 			{
	// 				size_t len = errorFile.length();
	// 				fd = errorFile.open(O_RDONLY);
	// 				fdBuffer = FileDescriptorBuffer::from(*fd, FileDescriptorBuffer::CLOSE | FileDescriptorBuffer::DELETE);
					
	// 				response.body(new FileResponseBody(*fdBuffer, len));

	// 				success = true;
	// 			}
	// 			catch (Exception &exception)
	// 			{
	// 				if (fdBuffer)
	// 					DeleteHelper::pointer<FileDescriptorBuffer>(fdBuffer);
	// 				else
	// 					DeleteHelper::pointer<FileDescriptor>(fd); /* In case of memory allocation failing for the body. */

	// 				if (LOG.isDebugEnabled())
	// 					LOG.debug() << "Failed to open custom error file: " << exception.message() << std::endl;
	// 			}
	// 		}
	// 	}
	// }

	if (!success)
		res.body(Page::instance().resolve(state));
	
	maker.executeMaker();
}
