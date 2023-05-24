#include "PathParser.hpp"
#include "../../file/File.hpp"
#include <iostream>

long PathParser::maxLength = 2 * 1024 * 1024;

PathParser::PathParser(void) {
	init(); 
}

void PathParser::init(void) {
	m_state = PathParser::PATH;
	_path = "/";
	m_original = _path;
	m_queryKey.clear();
	m_queryValue.clear();
	m_hexBeforeState = PathParser::PATH;
	m_hex.clear();
	m_query.clear();
	m_fragment.clear();
	m_dot = 0;
	m_level = 0;
}

void PathParser::clear() {
	init();
}


void PathParser::parse(char c) {
	switch (m_state)
	{
		case PathParser::PATH:
		{
			if (c == ' ')
				m_state = PathParser::END;
			else if (c == '+')
				hexToPath(' ');
			else if (c == '%')
				hexStart(&PathParser::hexToPath);
			else if (c == '?')
				m_state = PathParser::QUERY_STRING_KEY;
			else if (c == '#')
				commitQueryKeyValue(PathParser::FRAGMENT);
			else
				hexToPath(c);

			break;
		}

		case PathParser::QUERY_STRING_KEY:
		{
			if (c == '=')
				m_state = PathParser::QUERY_STRING_VALUE;
			else if (c == '%')
				hexStart(&PathParser::hexToKey);
			else if (c == '#')
				commitQueryKeyValue(PathParser::FRAGMENT);
			else if (c == '+')
				hexToKey(' ');
			else if (c == ' ')
				commitQueryKeyValue(PathParser::END);
			else
				hexToKey(c);

			break;
		}

		case PathParser::QUERY_STRING_VALUE:
		{
			if (c == '%')
				hexStart(&PathParser::hexToValue);
			else if (c == '&')
				commitQueryKeyValue(PathParser::QUERY_STRING_KEY);
			else if (c == '#')
			{
				commitQueryKeyValue(PathParser::FRAGMENT);
			}
			else if (c == '+')
				hexToValue(' ');
			else if (c == ' ')
				commitQueryKeyValue(PathParser::END);
			else
				hexToValue(c);

			break;
		}

		case PathParser::FRAGMENT:
		{
			if (c == ' ')
				m_state = PathParser::END;
			else if (c == '%')
				hexStart(&PathParser::hexToFragment);
			else
				hexToFragment(c);

			break;
		}

		case PathParser::HEX_START:
		{
			m_hex.clear();
			m_hex += c;

			m_state = PathParser::HEX_END;

			break;
		}

		case PathParser::HEX_END:
		{
			m_hex += c;

			char h = Base::convert<char>(m_hex, Base::HEX);
			if (h == 0)
				throw Exception("Decoded hex value cannot be a null terminator");

			((this)->*(m_hexStorer))(h);
			m_state = m_hexBeforeState;

			break;
		}

		case PathParser::END:
			return;
	}

	m_original += c;

	if (m_original.size() >= (unsigned long)PathParser::maxLength)
		throw RuntimeException("too long url exception");
}

void PathParser::hexToPath(char c) {
	_path += c;

	if (c == '/') {
		if (m_dot == 2) {
			_path = File(_path).path();

			if (--m_level == -1)
				throw Exception("Out of root directory");
		} else
			m_level++;

		m_dot = 0;
	} else if (c == '.')
		m_dot++;
}

void PathParser::hexToKey(char c) {
	m_queryKey += c;
}

void PathParser::hexToValue(char c) {
	m_queryValue += c;
}

void PathParser::hexToFragment(char c) {
	m_fragment += c;
}

void PathParser::commitQueryKeyValue(State nextState) {
	m_query[m_queryKey] = m_queryValue;
	m_queryKey.clear();
	m_queryValue.clear();
	m_state = nextState;
}
