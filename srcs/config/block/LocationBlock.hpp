#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <string>
#include <iostream>

class LocationBlock {
private:
	std::string _path;
	std::string _index;
	
public:
	LocationBlock(void);
	LocationBlock(const LocationBlock& other);
	LocationBlock& operator=(const LocationBlock& other);
	~LocationBlock(void);

	void setIndex(std::string str);
	std::string getIndex(void);
	void setPath(std::string str);
	std::string getPath(void);
	void check(std::string key, std::string value);


};

#endif