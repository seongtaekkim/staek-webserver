#include "../../exception/Exception.hpp"
#include "HTTPLocationInterpretor.hpp"
#include <string>

HTTPLocationInterpretor::HTTPLocationInterpretor() :
		_state(NOT_STARTED),
		_path(""),
		_start(""),
		_end(""),
		_locationBlock(),
		_firstChar('0'),
		_lastChar('0') {}

HTTPLocationInterpretor::HTTPLocationInterpretor(std::string path, const LocationBlock *locationBlock) :
		_state(NOT_STARTED),
		_path(path),
		_start(""),
		_end(""),
		_locationBlock(locationBlock),
		_firstChar('0'),
		_lastChar('0') {}

HTTPLocationInterpretor::HTTPLocationInterpretor(const HTTPLocationInterpretor &other) :
		_state(other._state),
		_path(other._path),
		_start(other._start),
		_end(other._end),
		_locationBlock(other._locationBlock),
		_firstChar(other._firstChar),
		_lastChar(other._lastChar) {}

HTTPLocationInterpretor::~HTTPLocationInterpretor() {}

HTTPLocationInterpretor& HTTPLocationInterpretor::operator =(const HTTPLocationInterpretor& other) {
	if (this != &other) {
		_state = other._state;
		_path = other._path;
		_start = other._start;
		_end = other._end;
	}
	return (*this);
}

bool HTTPLocationInterpretor::next(char &c) {
	if (_path.empty())
		return (false);
	c = _path[0];
	_path.erase(0, 1);
	return (true);
}

void HTTPLocationInterpretor::parse(char &c) {
	switch (_state)
	{
		case NOT_STARTED:
		case CHECK:
		{
			if (c == ' ')
			{}
			else if (c == '/') {
				_start += c;
				_state = START;
			}
			break;
		}
		case START:
		{
			_start += c;
			break;
		}
		case END:
			break;
	}
	_lastChar = c;
}

const std::string& HTTPLocationInterpretor::start(void) {
	return (_start);
}

const std::string& HTTPLocationInterpretor::end(void) {
	return (_end);
}

const std::string& HTTPLocationInterpretor::exact(void) {
	return (_exact);
}

void HTTPLocationInterpretor::end(std::string &end) {
	_end = end;
}

const char& HTTPLocationInterpretor::firstChar(void) {
	return (_lastChar);
}

const char& HTTPLocationInterpretor::lastChar(void) {
	return (_lastChar);
}

void HTTPLocationInterpretor::setEnd(std::string end) {
	_end = end;
}

const LocationBlock* HTTPLocationInterpretor::locationBlock() {
	return (_locationBlock);	
}