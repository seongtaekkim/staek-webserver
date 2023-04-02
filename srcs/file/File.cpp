#include "File.hpp"
#include "../exception/IOException.hpp"
#include "../exception/IllegalArgumentException.hpp"

File::File(const std::string path) : _path(path) {}
File::File(const File &other) 
	: _path(other._path) {}
File::~File(void) throw() {}
File& File::operator=(const File &other) {
	if (this != &other) {
		this->_path = other._path;
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

bool File::isFile() const {
	return (S_ISREG(this->stat().st_mode));
}

bool File::isDir() const {
	return (S_ISDIR(stat().st_mode));
}

bool File::isExecutable() const {
	return (stat().st_mode & S_IXUSR);
}

bool File::create() {
	int fd;
	std::string copy = this->_path;
	std::string previousStr = "";
	std::size_t found;
	
	while ((found = copy.find('/')) != std::string::npos)
	{
		std::string newPath = copy.substr(0, found);
		std::string remainedPath = copy.substr(found + 1, std::string::npos);
		if (newPath == "./" || newPath == "/")
		{
			previousStr = newPath;
			copy = remainedPath;
		}
		else
		{
			File file(previousStr + "/" + newPath);
			if (!file.exists())
				::mkdir(file.path().c_str(), 0777);
			previousStr = newPath;
			copy = remainedPath;
		}

	}
	if ((fd = ::open(this->_path.c_str(), O_CREAT, 0666)) == -1)
		IOException("filed open file", errno);
	close(fd);
	return (true);
}

FileDescriptor* File::open(int flags, mode_t mode) const {
	int fd;

	if ((fd = ::open(this->_path.c_str(), mode)) == -1) {
		throw IOException("failed open file", errno);
	}
	FileDescriptor *f = new FileDescriptor(fd);
	f->setNonBlock();
	return (f);
}

void File::remove(void) const {
	if (this->isDir())
		::rmdir(this->_path.c_str());
	else if(this->isFile())
		::unlink(this->_path.c_str());
	else
		throw IllegalArgumentException(this->_path + " is not file, directory");
}

off_t File::size() const {
	return (stat().st_size);
}

std::string File::name()  {
	return (this->_path.substr(indexOfSeparator() + 1));
}

struct stat File::stat(void) const {
	struct stat _stat;
	if (::stat(this->_path.c_str(), &_stat) < 0) {
		throw IOException("don't have the file", errno);
	}
	return (_stat);
}

const std::string& File::path(void) const {
	return (this->_path);
}

std::list<File> File::list(void) const {
	struct stat st;
	if (::stat(this->_path.c_str(), &st) == -1)
		throw IOException("don't have the file", errno);

	if (!S_ISDIR(st.st_mode))
		throw IOException(this->_path, ENOTDIR);

	DIR *dir = ::opendir(this->_path.c_str());
	if (!dir)
		throw IOException(this->_path, ENOTDIR);

	std::list<File> files;
	struct dirent *entry;
	while ((entry = ::readdir(dir)))
		files.push_back(File(this->_path + '/' + entry->d_name));
	::closedir(dir);
	return (files);
}

std::string File::getExtension() {
	std::string::size_type index = indexOfExtension();
	if (index == std::string::npos)
		return ("");
	return (this->_path.substr(index + 1));
}

std::string::size_type File::indexOfSeparator(void) {
	return (this->_path.rfind(SLASH));
}

std::string::size_type File::indexOfExtension() {
	std::string::size_type extensionPos = this->_path.rfind(EXTENSION);

	if (indexOfSeparator() > extensionPos)
		return (std::string::npos);
	else 
		return (extensionPos);
}