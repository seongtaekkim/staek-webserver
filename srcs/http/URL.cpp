#include "URL.hpp"

URL::URL() : _path(), _queryParameters(), _fragment() {
}

URL::URL(const std::string &path, const std::map<std::string, std::string> queryParameters, const std::string fragment) :
		_path(path), _queryParameters(queryParameters), _fragment(fragment) {
}

URL::URL(const URL &other) :
		_path(other._path), _queryParameters(other._queryParameters), _fragment(other._fragment) {
}

URL::~URL() {}

URL& URL::operator= (const URL &other) {
	if (this != &other) {
		_path = other._path;
		_queryParameters = other._queryParameters;
		_fragment = other._fragment;
	}
	return (*this);
}

const std::string& URL::path() const {
	return (_path);
}

const std::map<std::string, std::string>& URL::queryParameters() const {
	return _queryParameters;
}

const std::string& URL::fragment() const {
	return (_fragment);
}

std::string URL::fullUrl(void) const {
	std::string out = _path;

	if (_queryParameters.size() > 0)
		out += "?" + queryString();
	if (_fragment.size() > 0)
		out += "#" + _fragment;

	return (out);
}

std::string
URL::queryString(void) const {
	std::string out;

	if (_queryParameters.size() > 0) {
		typedef std::map<std::string, std::string> map;

		const map &queryParams = _queryParameters;

		for (map::const_iterator it = queryParams.begin(); it != queryParams.end(); it++)
		{
			out += encode(it->first) + "=" + encode(it->second);
			out += "&";
		}
	}

	return (out);
}

// 디렉토리 제외 파일이름 get
bool URL::filename(std::string& out) const {
	if (_path.empty())
		return (false);

	std::string::size_type lastSlashPos = _path.rfind("/");

	if (lastSlashPos != std::string::npos)
		out = _path.substr(lastSlashPos + 1);
	else
		out = _path;

	return (true);
}


// extension get
bool URL::extension(std::string& out) const {
	std::string filename;
	if (!this->filename(filename))
		return (false);

	std::string::size_type lastDotPos = filename.rfind(".");
	if (lastDotPos == std::string::npos)
		return (false);
	out = filename.substr(lastDotPos + 1);
	return (true);
}

URL::Builder
URL::builder(void) const {
	return (Builder(*this));
}

URL::Builder::Builder() :
		_path(), _queryParameters(), _fragment() {
}

URL::Builder::Builder(const URL &url) :
		_path(url._path),
		_queryParameters(url._queryParameters),
		_fragment(url._fragment)
{
}

URL::Builder::Builder(const Builder &other) :
		_path(other._path),
		_queryParameters(other._queryParameters),
		_fragment(other._fragment)
{}

URL::Builder::~Builder() {}

URL::Builder&
URL::Builder::operator =(const Builder &other)
{
	if (this != &other)
	{
		_path = other._path;
		_queryParameters = other._queryParameters;
		_fragment = other._fragment;
	}

	return (*this);
}

URL::Builder&
URL::Builder::path(const std::string &path)
{
	_path = path;

	return (*this);
}

URL::Builder&
URL::Builder::appendPath(const std::string &content)
{
	_path += content;
	return (*this);
}

URL::Builder&
URL::Builder::queryParameters(const std::map<std::string, std::string> &queryParameters) {
	_queryParameters = queryParameters;
	return (*this);
}

URL::Builder& URL::Builder::fragment(const std::string &fragment) {
	_fragment = fragment;
	return (*this);
}

URL URL::Builder::build() {
	return (URL(_path, _queryParameters, _fragment));
}

std::string URL::encode(const std::string &input) {
	return (input);
}