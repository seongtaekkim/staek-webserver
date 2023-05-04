#ifndef PATHPARSER_HPP
#define PATHPARSER_HPP

#include <map>
#include <string>
#include "../../exception/RuntimeException.hpp"
#include "../../util/Base.hpp"

class Base;

class PathParser {
	public:
			typedef void
		(PathParser::*HexStorer)(char);
		enum State {
			PATH,
			QUERY_STRING_KEY,
			QUERY_STRING_VALUE,
			FRAGMENT,
			HEX_START,
			HEX_END,
			END,
		};

	public:
		static long maxLength;

	private:
		State m_state;
		State m_hexBeforeState;
		std::string _path;
		std::string m_original;
		std::string m_queryKey;
		std::string m_queryValue;
		std::string m_hex;
		std::map<std::string, std::string> m_query;
		std::string m_fragment;
		long m_dot;
		long m_level;

		HexStorer m_hexStorer;

	public:
		PathParser(void);
		void parse(char c);
		void init(void);
		void clear(void);

		inline State state() const {
			return (m_state);
		}

		inline const std::string& path() const {
			return (_path);
		}

		inline const std::string& original() const {
			return (_path);
		}

		const std::map<std::string, std::string>& query() const {
			return (m_query);
		}

		const std::string& fragment() const {
			return (m_fragment);
		}

	private:
		void hexToPath(char c);
		void hexToKey(char c);
		void hexToValue(char c);
		void hexToFragment(char c);
		void commitQueryKeyValue(State nextState);
		inline void
		hexStart(HexStorer hexStorer)
		{
			m_hexBeforeState = m_state;
			m_state = HEX_START;
			m_hexStorer = hexStorer;
		}
};

#endif
