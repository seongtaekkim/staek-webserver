#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../util/Singleton.hpp"
#include "Reader.hpp"
#include "block/RootBlock.hpp"
#include "Mime.hpp"
#include "../util/ReleaseResource.hpp"

#define CONFIG_FILE "default_webserv.conf"

class Config : public Singleton<Config> {
private:
	std::string			_file;
	RootBlock*			_root;
	const Mime*			_mime;

	Config(const Config& other);
	Config& operator=(const Config& other);
public:
	Config(void);
	virtual ~Config(void);
	const Mime* mime(void);
	RootBlock* rootBlock(void);
};

#endif