#ifndef HEADER_HPP
#define HEADER_HPP

#include <stddef.h>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "../util/Time.hpp"
#include "SHTTP.hpp"
#include "URL.hpp"
#include "../util/Base.hpp"

class Mime;
class URL;

class Header {
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

	public:
		typedef std::list<std::string> list;
		typedef list::const_iterator lconst_iterator;
		typedef std::map<std::string, list> map;
		typedef map::const_iterator mconst_iterator;

	private:
		map _data;

	public:
		Header(void);
		Header(map storage);
		Header(const Header &other);
		Header& operator=(const Header &other);
		virtual ~Header(void);
		inline bool operator==(const Header &other) const {
			return (_data == other._data);
		}

		Header& contentType(const std::string &MimeType);
			
		Header& host(const std::string &value);

		Header& location(const std::string &value);
		Header& location(const URL &url);

		Header& server(void);
		Header& server(const std::string &value);

		Header& transferEncoding(const std::string& value);
		Header& chunkedTransferEncoding(void);

		Header& connection(const std::string &value);

		Header& html(void);

		Header& append(const std::string &key, const std::string &value, bool folding = false);

		Header& merge(const Header &headerFields);

		const std::string get(const std::string &key) const;

		mconst_iterator begin(void) const;
		mconst_iterator end(void) const;

		std::string format(const std::string &seperator = SHTTP::CRLF) const;

		bool empty(void) const;
		void clear(void);
		map& data(void);
		const map& data(void) const;

		Header& contentLength(std::size_t length);
};

#endif
