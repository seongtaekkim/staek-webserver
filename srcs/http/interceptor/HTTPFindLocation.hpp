
#ifndef HTTPFINDLOCATION_HPP_
# define HTTPFINDLOCATION_HPP_

#include "../../config/block/ServerBlock.hpp"

class HTTPFindLocation {
	private:
		std::string _clientPath;
		std::list<LocationBlock*> _serverLocations;
		const LocationBlock* _locationBlock;
		
	public:
		HTTPFindLocation();
		HTTPFindLocation(std::string clientPath, std::list<LocationBlock*> serverBlock);
		HTTPFindLocation(const HTTPFindLocation& other);
		HTTPFindLocation& operator=(const HTTPFindLocation& other);
		~HTTPFindLocation();
		HTTPFindLocation& location(const LocationBlock* locationBlock);
		const LocationBlock* location(void) const;
		HTTPFindLocation& parse(void);
};

#endif