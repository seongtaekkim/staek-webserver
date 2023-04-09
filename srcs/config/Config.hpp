#ifndef CONFIG_HPP
#define CONFIG_HPP
//https://www.nginx.com/resources/wiki/start/topics/examples/full/
//https://12bme.tistory.com/366

#include "../util/Singleton.hpp"
#include "Reader.hpp"
#include "block/RootBlock.hpp"
#include "Mime.hpp"
#include "../util/ReleaseResource.hpp"


// config file로 바꿀것임
#define CONFIG_FILE "../../config/mime.types"

class Config : public Singleton<Config> {
private:
	std::string			_file;
	const RootBlock*	_root;
	const Mime*			_mime;

	Config(const Config& other);
	Config& operator=(const Config& other);
public:
	Config(void);
	virtual ~Config(void);
	const Mime* mime(void);
};

#endif