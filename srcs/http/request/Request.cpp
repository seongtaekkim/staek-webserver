#include "Request.hpp"

/* 
	OCCF
*/
Request::Request(void) : _resource(), _header() {}

Request::Request(const Header& header, const StatusLine& statusLine, const URL& url) :
		_statusLine(statusLine),
		_url(url),
		_header(header),
		// _method(),
		_resource(url.path())
{
}

Request::Request(const Request& __copy) : _resource(__copy._resource) {
	_body = __copy._body;
}

Request	Request::operator=(const Request& other) {
	if (this != &other) {
		this->_resource = other._resource;
		this->_body = other._body;
		this->_isChunked = other._isChunked;
		this->_statusLine = other._statusLine;
		this->_url = other._url;
		this->_header = other._header;
		this->_serverBlock = other._serverBlock;
		this->_locationBlock = other._locationBlock;
	}
	return (*this);
}

Request::~Request(void) {
	std::cout << "delete Request::~Request " << std::endl;
}

std::string Request::body() {
	return (_body);
}

File Request::targetFile() {
	return (File(root(), this->_resource));
}

std::string Request::root(void) const {
	if (this->_locationBlock) {
		if (!this->_locationBlock->getRoot().empty())
			return (this->_locationBlock->getRoot());
	}
	if (this->_serverBlock) {
		if (!this->_serverBlock->getRoot().empty()) {
			return (this->_serverBlock->getRoot());
		}
	}
	if (!Config::instance().rootBlock()->ServerBlockList().front()->getRoot().empty())
		return (Config::instance().rootBlock()->ServerBlockList().front()->getRoot());
	return (File::currentDir());
}

const URL& Request::url(void) const {
	return (this->_url);
}

const std::string Request::resource() const {
	return (this->_resource);
}

void Request::resource(const std::string &resource) {
	this->_resource = resource;
}

void Request::serverBlock(const ServerBlock& serverBlock) {
	this->_serverBlock = &serverBlock;
}

const ServerBlock* Request::serverBlock(void) const {
	return (this->_serverBlock);
}

void Request::locationBlock(const LocationBlock& locationBlock) {
	this->_locationBlock = &locationBlock;
}

const LocationBlock* Request::locationBlock(void) const {
	return (this->_locationBlock);
}