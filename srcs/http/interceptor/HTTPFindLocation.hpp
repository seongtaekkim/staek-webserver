
#ifndef HTTPFINDLOCATION_HPP_
# define HTTPFINDLOCATION_HPP_

#include "../../config/block/ServerBlock.hpp"


class HTTPFindLocation
{	
	private:
		std::string m_clientPath;
		std::list<LocationBlock*> m_serverLocations;
		const LocationBlock* m_locationBlock;
		
	public:
		HTTPFindLocation();
		HTTPFindLocation(std::string clientPath, std::list<LocationBlock*> serverBlock);
		HTTPFindLocation(const HTTPFindLocation &other);
		
		virtual
		~HTTPFindLocation();

		HTTPFindLocation&
		operator =(const HTTPFindLocation &other);

		HTTPFindLocation&
		location(const LocationBlock* locationBlock);
		
		const LocationBlock* location(void) const;

		HTTPFindLocation&
		parse(void);
};

#endif