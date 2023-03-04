#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include "FileDescriptor.hpp"

// #define EXTENSION_DELEMETER '.'
// #define DIRECT_DELEMETER '/'

class File {
private:
	int			_fd;
	std::string _name;
	std::string _extention;
	std::string _path;
public:
	File(void);
	//File(int fd);
	File(const File &other);
	virtual ~File(void);
	File& operator=(const File &other);

	bool exists() const;
	bool isFile() const;
	bool isDirectory() const;
	bool isExecutable() const;
	bool createFile() const;
	FileDescriptor*
	open(int flags, mode_t mode = 0) const;
	void remove(void) const;
	size_t length() const;
	std::string name() const;
	File absolutePath() const;
	File parent() const;
	inline const std::string&
	path() const { return (_path); }
};

#endif 