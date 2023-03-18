#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <sys/stat.h>
#include "FileDescriptor.hpp"

// #define EXTENSION_DELEMETER '.'
// #define DIRECT_DELEMETER '/'

/**
 * @brief file 객체 관리
 * @details file 생성,삭제,열기,찾기,파일위치 기능을 제공한다.
 * @author seongtki
 * @date 2023.03.23
 */
class File {
private:
	std::string _name;
	std::string _extention;
	std::string _path;
	File(void);
public:
	File(const std::string path);
	File(const File &other);
	virtual ~File(void) throw();
	File& operator=(const File &other);

	bool exists() const;
	bool isFile() const;
	bool isDirectory() const;
	bool isExecutable() const;
	bool createFile() const;
	FileDescriptor* open(int flags, mode_t mode = 0) const;
	void remove(void) const;
	size_t length() const;
	std::string name() const;
	inline const std::string& path() const { return (_path); }
	File absolutePath() const;
	File parent() const;
	struct stat getStat(void);
};

#endif 