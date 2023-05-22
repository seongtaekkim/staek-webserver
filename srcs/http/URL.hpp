#ifndef URL_HPP
#define URL_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>

class URL {
public:
	class Builder;

private:
	std::string _path;
	std::map<std::string, std::string> _queryParameters;
	std::string _fragment;

public:
	URL(void);
	URL(const std::string &path, const std::map<std::string, std::string> queryParameters, const std::string fragment);
	URL(const URL &other);
	URL& operator =(const URL &other);
	~URL(void);

	const std::string& path() const;
	const std::map<std::string, std::string>& queryParameters() const;
	const std::string& fragment() const;
	std::string fullUrl(void) const;
	std::string queryString(void) const;
	bool filename(std::string &out) const;
	bool extension(std::string &out) const;
	Builder builder(void) const;
public:
	static std::string encode(const std::string &input);

public:
	class Builder {
		private:
			std::string _path;
			std::map<std::string, std::string> _queryParameters;
			std::string _fragment;

		public:
			Builder(void);
			Builder(const URL &url);
			Builder(const Builder &other);

			virtual ~Builder();
			Builder& operator=(const Builder &other);
			Builder& path(const std::string &path);
			Builder& appendPath(const std::string &content);
			Builder& queryParameters(const std::map<std::string, std::string> &queryParameters);
			Builder& fragment(const std::string &fragment);
			URL build();
	};
};

#endif
