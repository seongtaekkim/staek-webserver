#include "Header.hpp"
#include <set>
#include "URL.hpp"
#include "../util/Time.hpp"

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

Header::Header(void) :
		m_storage()
{
}

Header::Header(map storage) :
		m_storage(storage)
{
}

Header::Header(const Header &other) :
		m_storage(other.m_storage)
{
}

Header::~Header()
{
}

Header&
Header::operator=(const Header &other)
{
	if (this != &other)
		m_storage = other.m_storage;

	return (*this);
}

Header&
Header::acceptCharsets(const std::string &value)
{
	return (set(ACCEPT_CHARSETS, value));
}

Header&
Header::acceptLanguage(const std::string &value)
{
	return (set(ACCEPT_LANGUAGE, value));
}

Header&
Header::allow(const Method &method)
{
	return (allow(method.name()));
}

Header&
Header::allow(const std::vector<const Method*> &methods)
{
	if (methods.empty())
		return (*this);

	return (allow(Convert::join(methods)));
}

Header&
Header::allow(const std::list<const Method*> &methods)
{
	if (methods.empty())
		return (*this);

	return (allow(Convert::join(methods)));
}

Header&
Header::allow(const std::string &value)
{
	return (set(ALLOW, value));
}

Header&
Header::authorization(const std::string &type, const std::string &credentials)
{
	return (authorization(type + " " + credentials));
}

Header&
Header::authorization(const std::string &value)
{
	return (set(AUTHORIZATION, value));
}

Header&
Header::contentLanguage(const std::string &value)
{
	return (set(CONTENT_LANGUAGE, value));
}

Header&
Header::contentLocation(const std::string &value)
{
	return (set(CONTENT_LOCATION, value));
}

Header&
Header::contentLength(size_t length)
{
	return (set(CONTENT_LENGTH, Convert::toString(length)));
}

Header&
Header::contentType(const MIMERegistry &registry, const std::string &extension)
{
	const MIME *mime = registry.findByFileExtension(extension);

	if (mime)
		return (contentType(*mime));

	return (*this);
}

Header&
Header::contentType(const std::string &mimeType)
{
	return (set(CONTENT_TYPE, mimeType));
}

Header&
Header::contentType(const Mime &mime)
{
	return (set(CONTENT_TYPE, mime.type()));
}

Header&
Header::contentType(const const Mime* &optional)
{
	if (optional.absent())
		return (*this);

	return (set(CONTENT_TYPE, optional.get()->type()));
}

Header&
Header::date(void)
{
	return (date(Time::NOW()));
}

Header&
Header::date(const Time &date)
{
	return (this->date(date.format()));
}

Header&
Header::date(const std::string &value)
{
	return (set(DATE, value));
}

Header&
Header::host(const std::string &value)
{
	return (set(HOST, value));
}

Header&
Header::lastModified(long seconds)
{
	return (lastModified(Time(seconds)));
}

Header&
Header::lastModified(const Time &time)
{
	return (lastModified(Time(time)));
}

Header&
Header::lastModified(const std::string &date)
{
	return (lastModified(date));
}

Header&
Header::lastModified(const std::string &value)
{
	return (set(LAST_MODIFIED, value));
}

Header&
Header::location(const std::string &value)
{
	return (set(LOCATION, value));
}

Header&
Header::location(const URL &url)
{
	return (location(url.fullUrl()));
}

Header&
Header::referer(const std::string &value)
{
	return (set(REFERER, value));
}

Header&
Header::retryAfter(size_t seconds)
{
	return (retryAfter(Convert::toString(seconds)));
}

Header&
Header::retryAfter(const std::string &date)
{
	return (retryAfter(date));
}

Header&
Header::retryAfter(const std::string &value)
{
	return (set(RETRY_AFTER, value));
}

Header&
Header::server(void)
{
	return (server(APPLICATION_NAME));
}

Header&
Header::server(const std::string &value)
{
	return (set(SERVER, value));
}

Header&
Header::transferEncoding(const std::vector<std::string> &encodings)
{
	return (transferEncoding(Convert::join(encodings)));
}

Header&
Header::transferEncoding(const std::list<std::string> &encodings)
{
	return (transferEncoding(Convert::join(encodings)));
}

Header&
Header::transferEncoding(const std::string &value)
{
	return (set(TRANSFER_ENCODING, value));
}

Header&
Header::chunkedTransferEncoding(void)
{
	return (transferEncoding(CHUNKED));
}

Header&
Header::userAgent(const std::string &value)
{
	return (set(USER_AGENT, value));
}

Header&
Header::wwwAuthenticate(const std::string &type)
{
	return (set(WWW_AUTHENTICATE, type));
}

Header&
Header::wwwAuthenticate(const std::string &type, const std::string realm)
{
	if (realm.size() > 0)
		return (set(WWW_AUTHENTICATE, type + " realm=\"" + realm + "\""));

	return (wwwAuthenticate(type));
}

Header&
Header::connection(const std::string &value)
{
	return (set(CONNECTION, value));
}

Header&
Header::html(void)
{
	return (contentType(MIME_HTML));
}

Header&
Header::httpMessage(void)
{
	return (contentType(MIME_HTTP));
}

Header&
Header::set(const std::string &key, const std::string &value, bool folding)
{
	static std::string comaAndASpace = ", ";

	list &lst = m_storage[key];

	if (lst.empty() || key == SET_COOKIE)
		lst.push_back(value);
	else
	{
		if (folding)
			lst.front() += comaAndASpace + value; /* RFC 7230 - 3.2.2 */
		else
			lst.front() = value;
	}

	return (*this);
}

Header&
Header::merge(const Header &headerFields)
{
	for (mconst_iterator it = headerFields.begin(); it != headerFields.end(); it++)
		m_storage[it->first] = it->second;

	return (*this);
}

const Optional<std::string>
Header::get(const std::string &key) const
{
	mconst_iterator it = m_storage.find(key);

	if (it == m_storage.end())
		return (Optional<std::string>());

	return (Optional<std::string>::onlyIf(!it->second.empty(), it->second.front()));
}

Header::mconst_iterator
Header::begin(void) const
{
	return (m_storage.begin());
}

Header::mconst_iterator
Header::end(void) const
{
	return (m_storage.end());
}

std::string
Header::format(const std::string &separator) const
{
	static std::string colonAndASpace = ": ";

	std::string str;

	for (mconst_iterator it = begin(); it != end(); it++)
	{
		const list &lst = it->second;

		for (lconst_iterator lit = lst.begin(); lit != lst.end(); lit++)
			str += it->first + colonAndASpace + *lit + separator;
	}

	return (str);
}

bool
Header::empty(void) const
{
	return (m_storage.empty());
}

void
Header::clear(void)
{
	return (m_storage.clear());
}

Header::map&
Header::storage(void)
{
	return (m_storage);
}

const Header::map&
Header::storage(void) const
{
	return (m_storage);
}
