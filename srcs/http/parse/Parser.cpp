#include "Parser.hpp"
#include "../server/Client.hpp"
#include "../exception/UnsupportedVersionException.hpp"
#include "../exception/TooBigHeaderException.hpp"
#include "../exception/PayloadTooBigException.hpp"
#include "../../util/Base.hpp"

class Client;

long Parser::headerMaxLength = 8 * 1024;

Parser::Parser(Client& client) : _state(Parser::NOT_STARTED), _pathParser(), _headerSize(0), _header(), _bodyDecoder(), _client(client), _major(0), _minor(0), _clientMaxBodySize(0) {
	_isMax = false;
	_hState = Parser::FIELD;
}

Parser::~Parser(void) {
	if (_bodyDecoder)
		delete _bodyDecoder;
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
			if (c == ' ')
			{
				if (_state == Parser::NOT_STARTED)
					throw Exception("No method");
				_state = Parser::SPACES_BEFORE_PATH;
			}
			else
			{
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
			if (!std::isdigit(c))
				throw Exception("Expected a number");

			_major = c - '0';
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
			if (!std::isdigit(c))
				throw Exception("Expected a number");

			_minor = c - '0';
			_state = Parser::HTTP_MINOR;

			break;
		}

		case Parser::HTTP_MINOR:
		{
			if (_major != SHTTP::MAJOR || _minor != SHTTP::MINOR)
				throw UnsupportedVersionException(Base::toString(_major, 10) + "/" + Base::toString(_minor, 10) + " is not supported version");

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
			this->headerParse(c);
			if (this->hState() == Parser::HEND)
				_state = Parser::END;
			break;
		}

		case Parser::BODY:
			_state = Parser::BODY_DECODE;
			_bodyDecoder = HTTPBodyEncoding::decodeSelector(this->_header);
			if (_bodyDecoder == NULL) {
				_state = Parser::END;
				break;
			}
			if (c == 0)
				break;
		case Parser::BODY_DECODE:
		{
			size_t consumed = 0;

			bool finished = _bodyDecoder->parse(_client.in().storage(), _client.body(), consumed, _isMax);
			_client.in().clear();
			if (this->_clientMaxBodySize != 0 && (unsigned long)_client.body().size() > this->_clientMaxBodySize) {
					throw PayloadTooBigException();
			}
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


int Parser::state(void) {
	return (this->_state);
}

void Parser::state(int state) {
	this->_state = state;
}


void Parser::headerParse(char c) {
	switch (this->_hState)
	{
		case Parser::FIELD:
		{
			if (c == ' ')
			{
				if (m_key.empty())
					throw Exception("Space before field");
				else
					throw Exception("Space after field");
			}
			else if (c == ':')
				_hState = Parser::COLON;
			else
				m_key += c;

			break;
		}
		case Parser::COLON:
		{
			if (c == ' ')
				_hState = Parser::SPACES_BEFORE_VALUE;
			else
			{
				_hState = Parser::VALUE;
				m_value += c;
			}

			break;
		}
		case Parser::SPACES_BEFORE_VALUE:
		{
			if (c != ' ')
			{
				_hState = Parser::VALUE;
				m_value += c;
			}

			break;
		}
		case Parser::VALUE:
		{
			if (c == ' ')
				_hState = Parser::SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(Parser::HEND_R);
			else if (c == '\n')
				commit(Parser::HEND_N);
			else
				m_value += c;

			break;
		}

		case Parser::SPACES_AFTER_VALUE:
		{
			if (c == ' ')
				_hState = Parser::SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(Parser::HEND_R);
			else if (c == '\n')
				commit(Parser::HEND_N);
			else
			{
				m_value += ' ';
				m_value += c;
				_hState = Parser::VALUE;
			}

			break;
		}
		case Parser::HEND_R:
		{
			if (c == '\n')
				_hState = Parser::HEND_N;
			else
				throw Exception("Expected a \\n");

			break;
		}
		case Parser::HEND_N:
		{
			if (c == '\r')
				_hState = Parser::HEND_R2;
			else if (c == '\n')
				_hState = Parser::HEND;
			else
			{
				m_key += c;
				_hState = Parser::FIELD;
			}

			break;
		}
		case Parser::HEND_R2:
		{
			if (c == '\n')
				_hState = Parser::HEND;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case Parser::HEND:
			return;
	}
	this->_headerSize += 1;
	if (this->_headerSize >= Parser::headerMaxLength)
		throw TooBigHeaderException("too big header size exception");
}

void Parser::commit(Parser::HSTATE nextState) {
	_header.append(m_key, m_value, true);

	m_key.clear();
	m_value.clear();

	_hState = nextState;
}

void Parser::headerClear(void) {
	_hState = Parser::FIELD;
	_header.clear();
	m_key.clear();
	m_value.clear();
	_headerSize = 0;
}

int Parser::hState(void) const {
	return (this->_hState);
}

void Parser::hState(int state) {
	this->_hState = state;
}

const Header& Parser::header(void) const {
	return (this->_header);
}


unsigned long Parser::clientMaxBodySize(void) const {
	return (this->_clientMaxBodySize);
}

void Parser::clientMaxBodySize(unsigned long size) {
	this->_clientMaxBodySize = size;
}