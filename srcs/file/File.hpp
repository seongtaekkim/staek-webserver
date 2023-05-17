#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <list>
#include "FileDescriptor.hpp"


#define EXTENSION '.'
#define SLASH '/'

/**
 * @brief file 객체 관리
 * @details file 생성,삭제,열기,찾기,파일위치 기능을 제공한다.
 * @author seongtki
 * @date 2023.03.23
 */
class File {
private:
	std::string _path;
	File(void);
public:
	File(const std::string path);
	File(const File &other);
	File(const File &parent, const std::string &path);
			File(const File &parent, const File &child);
	File(const std::string &root, const std::string &resource);
	virtual ~File(void) throw();
	File& operator=(const File &other);

	bool exists() const;
	bool isFile() const;
	bool isDir() const;
	bool isExecutable() const;
	bool create(void);
	FileDescriptor* open(int flags, mode_t mode) const;
	void remove(void) const;
	off_t size(void) const;
	std::string name();
	const std::string& path(void) const;
	std::list<File> list(void) const;
	struct stat stat(void) const;
	std::string getExtension();
	std::string::size_type indexOfSeparator(void);
	std::string::size_type indexOfExtension(void);
	std::string concatRootAndResource(const std::string& root, const std::string& resource);
	static std::string currentDir(void);
};

#endif