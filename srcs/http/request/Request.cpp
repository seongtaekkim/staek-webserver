#include "Request.hpp"

typedef std::map<std::string, std::vector<std::string> >	headers_table;

/* 
	OCCF
*/

Request::Request(void) : _resource() {}

Request::Request(const StatusLine& statusLine, const URL& url) :
		_statusLine(statusLine),
		_url(url),
		// _header(headers),
		// _method(),
		// _serverBlock(),
		// _locationBlock(),
		_resource(url.path())
{}

// Request::Request(const StatusLine& statusLine, const URL& url, const Header& header) :
// 		_statusLine(statusLine),
// 		_url(url),
// 		// _header(headers),
// 		_method(),
// 		_serverBlock(),
// 		_locationBlock(),
// 		_resource(url.path())
// {
// }


Request::Request(const Request& __copy) : _resource(__copy._resource) {
	_reqString = __copy._reqString;
	_requestLine = __copy._requestLine;
	_headers = __copy._headers;
	_body = __copy._body;
}

Request	Request::operator=(const Request& __copy)
{
	if (this != &__copy) {
		this->_url = __copy._url;

		_reqString = __copy._reqString;
		_requestLine = __copy._requestLine;
		_headers = __copy._headers;
		_body = __copy._body;
	}
	return (*this);
}

Request::~Request(void) {}

Request::Request(std::string __reqString)
: _reqString(__reqString)
{
	_requestLine = RequestParser::parseRequestLine(_reqString.getRequestLine());
	_headers = RequestParser::parseHeaders(_reqString.getHeaders());
	if (_headers._headers["Transfer-Encoding"].size() == 0)
		_isChunked = false;
	else
		_isChunked = _headers._headers["Transfer-Encoding"][0] == "chunked";
	_body = _isChunked ? RequestParser::parseBody(_reqString.getBody()) : _reqString.getBody();
}

RequestString	Request::getReqString() { return (_reqString); }
RequestLine		Request::getRequestLine() { return (_requestLine); }
RequestHeaders	Request::getHeaders() { return (_headers); }

e_method		Request::method() { return (_requestLine._method); }
std::string		Request::uri() { return (_requestLine._uri); }
float			Request::version() { return (_requestLine._version); }
headers_table	Request::headers() { return (_headers._headers); } 
std::string		Request::body() { return (_body); }
size_t			Request::header_count() { return (_headers._headerCount); }


File Request::targetFile() {
	return (File(root(), _url.path()));
}

std::string Request::root(void) const {
	// if (locationBlock).present())
	// {
	// 	const LocationBlock &locationBlock = *this->locationBlock().get();

	// 	if (locationBlock.root().present())
	// 		return (locationBlock.root().get());
	// }

	// if (serverBlock().present())
	// {
	// 	const ServerBlock &serverBlock = *this->serverBlock().get();

	// 	if (serverBlock.root().present())
	// 		return (serverBlock.root().get());
	// }

	// if (Configuration::instance().rootBlock().root().present())
	// 	return (Configuration::instance().rootBlock().root().get());
	// return (File::currentDirectory().path());
	
	return (File::currentDir());
}

const URL& Request::url(void) const {
	return (this->_url);
}