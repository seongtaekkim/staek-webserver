#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <string>
#include <iostream>

class LocationBlock {
private:
	std::string		_path;
	std::string		_index;
	std::string		_root;
	std::string		_autoindex;
	std::string		_limitExcept;
	unsigned long	_clientMaxBodySize;
public:
	LocationBlock(void);
	LocationBlock(const LocationBlock& other);
	LocationBlock& operator=(const LocationBlock& other);
	~LocationBlock(void);

	void setIndex(std::string str);
	std::string getIndex(void) const;
	void setPath(std::string str);
	std::string getPath(void) const;
	void setRoot(std::string str);
	std::string getRoot(void) const;
	void setAutoindex(std::string str);
	std::string getAutoindex(void) const;
	void setLimitExcept(std::string str);
	std::string getLimitExcept(void) const;
	void setClientMaxBodySize(std::string str);
	unsigned long getClientMaxBodySize(void) const;
	void check(std::string key, std::string value);

};

#endif