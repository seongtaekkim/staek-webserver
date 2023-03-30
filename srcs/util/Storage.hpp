#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>

class Storage {
public:
	typedef std::string::size_type SizeType;

private:
	std::string	_storage;
	SizeType	_maxSize;

public:
	Storage(void);
	Storage(const Storage& other);
	Storage& operator=(const Storage& other);
	virtual ~Storage(void);
	
	void clear(void);
	std::size_t capacity(void);
	std::string& store(std::string str);
	std::string& store(const void* buf, std::size_t ret);
	std::string& storage(void);
	std::size_t size(void) const;


};
#endif