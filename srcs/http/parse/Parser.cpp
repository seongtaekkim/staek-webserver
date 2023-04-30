#include "Parser.hpp"

Parser::Parser(void) : _state(Parser::NOT_STARTED), _pathParser() {}

Parser::~Parser(void) {}

std::vector<std::string>	Parser::split(std::string str, std::string delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delim.length());
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}

std::vector<std::string>	Parser::split(std::string str, char delim)
{
    std::vector<std::string>	tokens;
    size_t						pos = 0;
    std::string					token;

    while ((pos = str.find(delim)) != std::string::npos)
	{
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + 1);
    }
    if (str != "")
        tokens.push_back(str);
    return tokens;
}

void	Parser::trim(std::string& str)
{
    // Trim leading spaces
    std::string::iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        ++it;
    }
    str.erase(str.begin(), it);

    // Trim trailing spaces
    it = str.end();
    while (it != str.begin() && std::isspace(*(it - 1))) {
        --it;
    }
    str.erase(it, str.end());
}

std::string Parser::toupper(std::string str)
{
    std::string result;

    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if ('a' <= *it && *it <= 'z')
            result += char(*it - 'a' + 'A');
        else
            result += *it;
    }
    return result;
}

void Parser::parse(char c) {

	switch (this->_state)
	{
		case Parser::NOT_STARTED:
		{
			if (c == '\r' || c == '\n')
				break;
			else
				_state = Parser::METHOD;
		}
		case Parser::METHOD:
		{
			// m_max = false;
			if (c == ' ')
			{
				if (_state == Parser::NOT_STARTED)
					throw Exception("No method");
				_state = Parser::SPACES_BEFORE_PATH;
			}
			else
			{
				// if (!ft::isupper(c))
				// 	throw Exception("Method is only upper-case letter");

				// if (_method.length() > 20)
				// 	throw Exception("Method is over 20 characters");

				_state = Parser::METHOD;
				_method += c;
			}

			break;
		}

		case Parser::SPACES_BEFORE_PATH:
		{
			if (c != ' ')
			{
				if (c != '/')
					throw Exception("No slash");

				_state = Parser::PATH;
			}

			break;
		}

		case Parser::PATH:
		{
			_pathParser.parse(c);

			if (_pathParser.state() == PathParser::S_END)
				_state = Parser::HTTP_START;

			break;
		}

		case Parser::HTTP_START:
		{
			if (c != 'H')
				throw Exception("Expected `H`");

			_state = Parser::HTTP_H;

			break;
		}

		case Parser::HTTP_H:
		{
			if (c != 'T')
				throw Exception("Expected `T`");

			_state = Parser::HTTP_HT;

			break;
		}

		case Parser::HTTP_HT:
		{
			if (c != 'T')
				throw Exception("Expected `T`");

			_state = Parser::HTTP_HTT;

			break;
		}

		case Parser::HTTP_HTT:
		{
			if (c != 'P')
				throw Exception("Expected `P`");

			_state = Parser::HTTP_HTTP;

			break;
		}

		case Parser::HTTP_HTTP:
		{
			if (c != '/')
				throw Exception("Expected `/`");

			_state = Parser::HTTP_SLASH;

			break;
		}

		case Parser::HTTP_SLASH:
		{
			// if (!ft::isdigit(c))
				// throw Exception("Expected a number");

			// _major = c - '0';
			_state = Parser::HTTP_MAJOR;

			break;
		}

		case Parser::HTTP_MAJOR:
		{
			if (c != '.')
				throw Exception("Expected `.`");

			_state = Parser::HTTP_DOT;

			break;
		}

		case Parser::HTTP_DOT:
		{
			// if (!ft::isdigit(c))
				// throw Exception("Expected a number");

			// _minor = c - '0';
			_state = Parser::HTTP_MINOR;

			break;
		}

		case Parser::HTTP_MINOR:
		{
			// if (!HTTPVersion::isSupported(m_minor, m_major))
			// 	throw UnsupportedHTTPVersion::of(m_minor, m_major);

			if (c == '\r')
				_state = Parser::HTTP_END_R;
			else if (c == '\n')
				_state = Parser::HTTP_END_N;
			else
				throw Exception("Expected a \\r or \\n");

			break;
		}

		case Parser::HTTP_END_R:
		{
			if (c == '\n')
				_state = Parser::HTTP_END_N;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case Parser::HTTP_END_N:
		{
			if (c == '\r')
				_state = Parser::END_R;
			else if (c == '\n')
				_state = Parser::END;
			else
			{
				_state = Parser::HEADER_FIELDS;
				// m_headerFieldsParser.consume(c);
			}

			break;
		}

		case Parser::END_R:
		{
			if (c == '\n')
				_state = Parser::END;
			else
				_state = Parser::END;

			break;
		}

		case Parser::HEADER_FIELDS:
		{
			// m_headerFieldsParser.consume(c);

			// if (m_headerFieldsParser.state() == HTTPHeaderFieldsParser::S_END)
				_state = Parser::END;

			break;
		}

		case Parser::BODY:
			_state = Parser::BODY_DECODE;
			// _bodyDecoder = HTTPBodyEncoding::decoderFor(m_headerFieldsParser.headerFields());

			// if (m_bodyDecoder == NULL)
			// {
			// 	_state = Parser::END;
			// 	break;
			// }

			if (c == 0)
				break;

			// fall through

		case Parser::BODY_DECODE:
		{
			// size_t consumed = 0;
			// bool finished = m_bodyDecoder->consume(m_client.in().storage(), m_client.body(), consumed, m_max);

			// m_client.in().skip(consumed);
			// m_totalSize += consumed;

			// if (m_maxBodySize != -1 && (long long)m_client.body().size() > m_maxBodySize) // TODO This kept everything in RAM...
			// {
			// 	m_max = true;
			// 	if (finished)
			// 		throw HTTPRequestPayloadTooLargeException();
			// }

			// if (finished)
			// 	_state = Parser::END;

			break;
		}

		case Parser::END:
			break;

	}
}

PathParser Parser::pathParser(void) const {
    return (this->_pathParser);
}


std::string Parser::method(void) {
	return (this->_method);
}


Parser::STATE Parser::state(void) const {
	return (this->_state);
}
