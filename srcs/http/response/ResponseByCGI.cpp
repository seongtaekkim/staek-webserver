#include "ResponseByCGI.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../encode/ChunkEncoder.hpp"
#include "../cgi/CGITask.hpp"
#include "../server/Client.hpp"
#include "method/Method.hpp"
#include "../../util/Base.hpp"

ResponseByCGI::ResponseByCGI(Client& client, CGITask& task) : _client(client), _task(task), _isEnd(false) {}

ResponseByCGI::~ResponseByCGI(void) {}

bool ResponseByCGI::isSelfManaged() const {
	return (true);
}

bool ResponseByCGI::store(Storage& buffer) {

	bool hasResponseBody = this->_client.parser().method().compare("HEAD") != 0;

	if (hasResponseBody) {
		buffer.store(this->_task.out().storage());
	}
	this->_isEnd = true;
	return (true);
}

bool ResponseByCGI::isEnd(void) {
	return (this->_isEnd);
}