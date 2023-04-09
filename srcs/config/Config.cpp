#include "Config.hpp"

Config::Config(void) {
	std::cout << "constructor config" << std::endl;
	Reader::from(CONFIG_FILE).read();
	Mime *mime = new Mime("../../config/mime.types");
	RootBlock *rootBlock = new RootBlock();
	this->_file = CONFIG_FILE;
	this->_mime = mime;
	this->_root = rootBlock;
}

Config::~Config(void) {
	ReleaseResource::pointer<Mime>(this->_mime);
}

const Mime* Config::mime(void) {
	return (this->_mime);
}