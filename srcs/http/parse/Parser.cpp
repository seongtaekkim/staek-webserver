#include "Parser.hpp"

#include "../server/Client.hpp"

class Client;

long Parser::headerMaxLength = 8 * 1024 * 1024;

Parser::Parser(Client& client) : _state(Parser::NOT_STARTED),_hState(Parser::HSTATE::FIELD), _pathParser(), _header(), _client(client), _isMax(false) {}

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
		std::cout << "state : " << this->_state << std::endl;
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
			// std::cout << "_pathParser.path() : " << _pathParser.path() << std::endl;
			if (_pathParser.state() == PathParser::END)
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
				_state = Parser::STATE::END_R;
			else if (c == '\n')
				_state = Parser::STATE::END;
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
				_state = Parser::STATE::END;
			else
				_state = Parser::STATE::END;

			break;
		}

		case Parser::HEADER_FIELDS:
		{
			this->headerParse(c);
			if (this->hState() == Parser::HSTATE::HEND)
				_state = Parser::END;
			break;
		}

		case Parser::BODY:
			_state = Parser::BODY_DECODE;
			std::cout << "body!" << std::endl;
			_bodyDecoder = HTTPBodyEncoding::decoderFor(this->_header);

			if (_bodyDecoder == NULL)
			{
				_state = Parser::END;
				break;
			}

			if (c == 0)
				break;

			// fall through

		case Parser::BODY_DECODE:
		{
			std::cout << "body!2" << std::endl;
			size_t consumed = 0;

			bool finished = _bodyDecoder->consume(_client.in().storage(), _client.body(), consumed, _isMax);

			// _client.in().skip(consumed);
			_client.in().clear();
			// m_totalSize += consumed;

			// if (m_maxBodySize != -1 && (long long)m_client.body().size() > m_maxBodySize) // TODO This kept everything in RAM...
			// {
			// 	m_max = true;
			// 	if (finished)
			// 		throw HTTPRequestPayloadTooLargeException();
			// }

			if (finished)
				this->_state = Parser::END;
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


Parser::STATE Parser::state(void) {
	return (this->_state);
}

void Parser::state(Parser::STATE state) {
	this->_state = state;
}


void Parser::headerParse(char c) {
	switch (this->_hState)
	{
		case Parser::HSTATE::FIELD:
		{
			if (c == ' ')
			{
				if (m_key.empty())
					throw Exception("Space before field");
				else
					throw Exception("Space after field");
			}
			else if (c == ':')
				_hState = Parser::HSTATE::COLON;
			else
				m_key += c;

			break;
		}
		case Parser::HSTATE::COLON:
		{
			if (c == ' ')
				_hState = Parser::HSTATE::SPACES_BEFORE_VALUE;
			else
			{
				_hState = Parser::HSTATE::VALUE;
				m_value += c;
			}

			break;
		}
		case Parser::HSTATE::SPACES_BEFORE_VALUE:
		{
			if (c != ' ')
			{
				_hState = Parser::HSTATE::VALUE;
				m_value += c;
			}

			break;
		}
		case Parser::HSTATE::VALUE:
		{
			if (c == ' ')
				_hState = Parser::HSTATE::SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(Parser::HSTATE::HEND_R);
			else if (c == '\n')
				commit(Parser::HSTATE::HEND_N);
			else
				m_value += c;

			break;
		}

		case Parser::HSTATE::SPACES_AFTER_VALUE:
		{
			if (c == ' ')
				_hState = Parser::HSTATE::SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(Parser::HSTATE::HEND_R);
			else if (c == '\n')
				commit(Parser::HSTATE::HEND_N);
			else
			{
				m_value += ' ';
				m_value += c;
				_hState = Parser::HSTATE::VALUE;
			}

			break;
		}
		case Parser::HSTATE::HEND_R:
		{
			if (c == '\n')
				_hState = Parser::HSTATE::HEND_N;
			else
				throw Exception("Expected a \\n");

			break;
		}
		case Parser::HSTATE::HEND_N:
		{
			if (c == '\r')
				_hState = Parser::HSTATE::HEND_R2;
			else if (c == '\n')
				_hState = Parser::HSTATE::HEND;
			else
			{
				m_key += c;
				_hState = Parser::HSTATE::FIELD;
			}

			break;
		}
		case Parser::HSTATE::HEND_R2:
		{
			if (c == '\n')
				_hState = Parser::HSTATE::HEND;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case Parser::HSTATE::HEND:
			return;
	}
	this->_headerSize += 1;
	// std::cout << "_hState : " << _hState << std::endl; 
	if (this->_headerSize >= Parser::headerMaxLength)
		throw Exception("too long header exception");
}

void Parser::commit(Parser::HSTATE nextState) {
	_header.append(m_key, m_value, true);

	m_key.clear();
	m_value.clear();

	_hState = nextState;
}

void Parser::headerClear(void) {
	_hState = Parser::HSTATE::FIELD;
	_header.clear();
	m_key.clear();
	m_value.clear();
	_headerSize = 0;
}

Parser::HSTATE Parser::hState(void) const {
	return (this->_hState);
}

const Header& Parser::header(void) const {
	return (this->_header);
}