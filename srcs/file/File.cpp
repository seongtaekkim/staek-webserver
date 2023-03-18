#include "File.hpp"
#include "../exception/IOException.hpp"

File::File(const std::string path) : _path(path) {}
File::File(const File &other) 
	: _path(other._path), _name(other._name), _extention(other._extention) {}
File::~File(void) throw() {}
File& File::operator=(const File &other) {
	if (this != &other) {
		this->_path = other._path;
		this->_extention = other._extention;
		this->_name = other._name;
	}
	return (*this);
}

/**
* @brief file 존재여부 체크
		- ::stat 함수를 이용해서 체크함.
* @exception 파일이 없는데 errno가 ENOENT가 아니라면 IOException 발생
* @date 2023.03.23
*/
bool File::exists() const {
	struct stat _stat;
	if (::stat(this->_path.c_str(), &_stat) < 0) {
		int errorno = errno;
		if (errorno == ENOENT)
			return (false);
		errno = 0;
		throw IOException("don't have the file", errorno);
	}
	return (true);
}

bool File::isFile() const {}
bool File::isDirectory() const {
	//     const char* path = "dir"; // 경로
    // if (stat(path, &statbuf) != -1) {
    //     if (S_ISDIR(statbuf.st_mode)) { // 디렉토리인지 확인
    //         cout<<"Path exist!! ==> "<<path<<endl;
    //     }
    // } else {
    //     cout<<"No path ==> "<<path<<endl;
    // }
}

bool File::isExecutable() const {}
bool File::createFile() const {}
FileDescriptor* File::open(int flags, mode_t mode = 0) const {}
void File::remove(void) const {}
size_t File::length() const {}
std::string File::name() const {}
File File::absolutePath() const {}
File File::parent() const {}

struct stat File::getStat(void) {
	struct stat _stat;
	if (::stat(this->_path.c_str(), &_stat) < 0) {
		throw IOException("don't have the file", errno);
	}
	return (_stat);
}
