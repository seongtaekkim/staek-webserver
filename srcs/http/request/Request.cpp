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
{}

Request::Request(const Request& __copy) : _resource(__copy._resource) {
	_body = __copy._body;
}

Request	Request::operator=(const Request& __copy) {
	if (this != &__copy) {
		this->_url = __copy._url;
		_body = __copy._body;
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
	// return (File(root(), this->_resource));
	return (File(root(), _url.path()));
}

std::string Request::root(void) const {
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