#include "Header.hpp"
#include <set>

const std::string Header::ACCEPT_CHARSETS		= "Accept-Charsets";
const std::string Header::ACCEPT_LANGUAGE		= "Accept-Language";
const std::string Header::ALLOW					= "Allow";
const std::string Header::AUTHORIZATION			= "Authorization";
const std::string Header::CONTENT_LANGUAGE		= "Content-Language";
const std::string Header::CONTENT_LENGTH		= "Content-Length";
const std::string Header::CONTENT_LOCATION		= "Content-Location";
const std::string Header::CONTENT_TYPE			= "Content-Type";
const std::string Header::DATE					= "Date";
const std::string Header::HOST					= "Host";
const std::string Header::LAST_MODIFIED			= "Last-Modified";
const std::string Header::LOCATION 				= "Location";
const std::string Header::REFERER				= "Referer";
const std::string Header::RETRY_AFTER			= "Retry-After";
const std::string Header::SERVER				= "Server";
const std::string Header::TRANSFER_ENCODING		= "Transfer-Encoding";
const std::string Header::USER_AGENT			= "User-Agent";
const std::string Header::WWW_AUTHENTICATE		= "WWW-Authenticate";
const std::string Header::SET_COOKIE			= "Set-Cookie";
const std::string Header::CONNECTION			= "Connection";
const std::string Header::STATUS				= "Status";
const std::string Header::MIME_HTML				= "text/html";
const std::string Header::MIME_HTTP				= "message/http";
const std::string Header::CHUNKED				= "chunked";
const std::string Header::CLOSE					= "close";
const std::string Header::KEEP_ALIVE			= "keep-alive";

Header::Header(void) : _data() {}

Header::Header(map storage) : _data(storage) {}

Header::Header(const Header &other) : _data(other._data) {}

Header::~Header(void) {}

Header& Header::operator=(const Header& other) {
	if (this != &other)
		_data = other._data;
	return (*this);
}

Header& Header::host(const std::string &value) {
	return (append(HOST, value));
}

Header& Header::location(const std::string &value) {
	return (append(LOCATION, value));
}

Header& Header::location(const URL &url) {
	return (location(url.fullUrl()));
}

Header& Header::server(void) {
	return (server(SHTTP::APPLICATION_NAME));
}

Header& Header::server(const std::string& value) {
	return (append(SERVER, value));
}

Header& Header::transferEncoding(const std::string& value) {
	return (append(TRANSFER_ENCODING, value));
}

Header& Header::chunkedTransferEncoding(void) {
	return (transferEncoding(CHUNKED));
}

Header& Header::connection(const std::string& value) {
	return (append(CONNECTION, value));
}

Header& Header::contentType(const std::string &mimeType) {
	return (append(CONTENT_TYPE, mimeType));
}

Header& Header::mimeHTML(void) {
	return (contentType(MIME_HTML));
}


Header& Header::append(const std::string &key, const std::string &value, bool folding) {
	static std::string comaAndASpace = ", ";

	list &lst = _data[key];

	if (lst.empty() || key == SET_COOKIE)
		lst.push_back(value);
	else
	{
		if (folding)
			lst.front() += comaAndASpace + value;
		else
			lst.front() = value;
	}

	return (*this);
}

Header& Header::merge(const Header &headerFields) {
	for (mconst_iterator it = headerFields.begin(); it != headerFields.end(); it++)
		_data[it->first] = it->second;
	return (*this);
}

const std::string Header::get(const std::string &key) const {
	mconst_iterator it = _data.find(key);

	if (it == _data.end())
		return (std::string(""));
	if (!it->second.empty())
		return (it->second.front());
	else
		return (std::string(""));
}

Header::mconst_iterator Header::begin(void) const {
	return (_data.begin());
}

Header::mconst_iterator Header::end(void) const {
	return (_data.end());
}

std::string Header::format(const std::string &separator) const {
	static std::string colonAndASpace = ": ";

	std::string str;

	for (mconst_iterator it = begin(); it != end(); it++) {
		const list &lst = it->second;
		for (lconst_iterator lit = lst.begin(); lit != lst.end(); lit++)
			str += it->first + colonAndASpace + *lit + separator;
	}

	return (str);
}

bool Header::empty(void) const {
	return (_data.empty());
}

void Header::clear(void) {
	return (_data.clear());
}

Header::map& Header::data(void) {
	return (_data);
}

const Header::map& Header::data(void) const {
	return (_data);
}

Header& Header::contentLength(std::size_t length) {
	return (append(CONTENT_LENGTH, Base::toString(length, 10)));
}

Header& Header::allow(const std::string& value) {
	return (append(ALLOW, value));
}

Header& Header::lastModified(const std::string &value) {
	return (append(LAST_MODIFIED, value));
}