#ifndef HEADER_HPP
#define HEADER_HPP

#include <stddef.h>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "../util/Time.hpp"
#include "response/method/Method.hpp"
#include "SHTTP.hpp"

class Mime;
class URL;

class Header {
	public:
		typedef std::list<std::string> list;
		typedef list::const_iterator lconst_iterator;

		// typedef std::map<std::string, list, StringUtils::InsensitiveCompare> map;
		typedef std::map<std::string, list> map;
		typedef map::const_iterator mconst_iterator;

	private:
		map m_storage;

	public:
		Header(void);
		Header(map storage);
		Header(const Header &other);
		Header& operator=(const Header &other);
		virtual ~Header();

		inline bool
		operator ==(const Header &other) const
		{
			return (m_storage == other.m_storage);
		}

		Header&
		acceptCharsets(const std::string &value);

		Header&
		acceptLanguage(const std::string &value);

		Header&
		allow(const Method &method);

		Header&
		allow(const std::vector<const Method*> &methods);

		Header&
		allow(const std::list<const Method*> &methods);

		Header&
		allow(const std::string &value);

		Header&
		authorization(const std::string &value);

		Header&
		authorization(const std::string &type, const std::string &credentials);

		Header&
		contentLanguage(const std::string &value);

		Header&
		contentLength(size_t length);

		Header&
		contentLocation(const std::string &value);

		// Header&
		// contentType(const MimeRegistry &registry, const std::string &extension);

		Header&
		contentType(const std::string &MimeType);

		Header&
		contentType(const Mime &Mime);

		Header&
		contentType(const Mime* &optional);

		Header&
		date(void);

		Header&
		date(const std::string &date);

		Header&
		date(const std::string &value);

		Header&
		host(const std::string &value);

		Header&
		lastModified(long seconds);

		Header&
		lastModified(const Time &time);

		Header&
		lastModified(const std::string &date);

		Header&
		lastModified(const std::string &value);

		Header&
		location(const std::string &value);

		Header&
		location(const URL &url);

		Header&
		referer(const std::string &value);

		Header&
		retryAfter(size_t seconds);

		Header&
		retryAfter(const std::string &date);

		Header&
		retryAfter(const std::string &value);

		Header&
		server(void);

		Header&
		server(const std::string &value);

		Header&
		transferEncoding(const std::vector<std::string> &encodings);

		Header&
		transferEncoding(const std::list<std::string> &encodings);

		Header&
		transferEncoding(const std::string &value);

		Header&
		chunkedTransferEncoding(void);

		Header&
		userAgent(const std::string &value);

		Header&
		wwwAuthenticate(const std::string &type);

		Header&
		wwwAuthenticate(const std::string &type, const std::string &realm);

		Header&
		wwwAuthenticate(const std::string &type, const std::string realm);

		Header&
		connection(const std::string &value);

		Header&
		html(void);

		Header&
		httpMessage(void);

		Header&
		set(const std::string &key, const std::string &value, bool folding = false);

		Header&
		merge(const Header &headerFields);

		const std::string get(const std::string &key) const;

		mconst_iterator begin(void) const;
		mconst_iterator end(void) const;

		std::string format(const std::string &seperator = SHTTP::CRLF) const;

		bool empty(void) const;
		void clear();
		map& storage(void);
		const map& storage(void) const;

	public:
		static const std::string ACCEPT_CHARSETS;
		static const std::string ACCEPT_LANGUAGE;
		static const std::string ALLOW;
		static const std::string AUTHORIZATION;
		static const std::string CONTENT_LANGUAGE;
		static const std::string CONTENT_LENGTH;
		static const std::string CONTENT_LOCATION;
		static const std::string CONTENT_TYPE;
		static const std::string DATE;
		static const std::string HOST;
		static const std::string LAST_MODIFIED;
		static const std::string LOCATION;
		static const std::string REFERER;
		static const std::string RETRY_AFTER;
		static const std::string SERVER;
		static const std::string TRANSFER_ENCODING;
		static const std::string USER_AGENT;
		static const std::string WWW_AUTHENTICATE;
		static const std::string SET_COOKIE;
		static const std::string CONNECTION;
		static const std::string STATUS;
		static const std::string MIME_HTML;
		static const std::string MIME_HTTP;
		static const std::string CHUNKED;
		static const std::string CLOSE;
		static const std::string KEEP_ALIVE;
};

#endif
