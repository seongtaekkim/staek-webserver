
#include "../../config/block/LocationBlock.hpp"
#include "HTTPFindLocation.hpp"
#include "HTTPLocationInterpretor.hpp"
#include <cstddef>
#include <iostream>
#include <list>
#include <string>

HTTPFindLocation::HTTPFindLocation() :
		_clientPath(""),
		_serverLocations(),
		_locationBlock() {}

HTTPFindLocation::HTTPFindLocation(std::string clientPath, std::list<LocationBlock*> serverLocations) :
		_clientPath(clientPath),
		_serverLocations(serverLocations),
		_locationBlock() {}

HTTPFindLocation::HTTPFindLocation(const HTTPFindLocation &other) :
		_clientPath(other._clientPath),
		_serverLocations(other._serverLocations),
		_locationBlock(other._locationBlock) {}

HTTPFindLocation::~HTTPFindLocation(void) {}

HTTPFindLocation&
HTTPFindLocation::operator =(const HTTPFindLocation &other) {
	if (this != &other) {
		_clientPath = other._clientPath;
		_serverLocations = other._serverLocations;
		_locationBlock = other._locationBlock;
	}
	return (*this);
}

HTTPFindLocation&
HTTPFindLocation::location(const LocationBlock *locationBlock) {
	_locationBlock = locationBlock;

	return (*this);
}

const LocationBlock* HTTPFindLocation::location(void) const {
	return (_locationBlock);
}

HTTPFindLocation& HTTPFindLocation::parse(void) {
	std::list<LocationBlock*>::iterator it = _serverLocations.begin();
	std::list<LocationBlock*>::iterator ite = _serverLocations.end();

	int start;
	int endIndicator;
	std::size_t pos;
	std::size_t new_pos;
	int not_found_middle;

	std::list<HTTPLocationInterpretor> possibleLocationList;
	
	while (it != ite) {
		HTTPLocationInterpretor interpretor((*it)->getPath(), *it);

		char c;
		start = 0;
		endIndicator = 0;
		pos = 0;
		new_pos = 0;
		not_found_middle = 0;

		while (interpretor.next(c))
			interpretor.parse(c);
	
		if (interpretor.firstChar() != '*') {
			if (!(interpretor.start().empty())) {
				if (_clientPath.compare(0, interpretor.start().size(), interpretor.start()) == 0 || (_clientPath + "/").compare(0, interpretor.start().size(), interpretor.start()) == 0)
				{
					start = 1;
					pos = interpretor.start().size();
				}
				else {
					it++;
					continue;
				}
			}
		}

		if (!(interpretor.end().empty())) {
			std::string end = interpretor.end();

			int size = end.size();
			int index = _clientPath.size() - size;
		
			if (index >= 0 && (_clientPath.compare(index, size, end) == 0 || (_clientPath + "/").compare(index, size, end) == 0)) {
				endIndicator = 1;
			}
			else {
				it++;
				continue;
			}
		}

		if (start || endIndicator) {
			possibleLocationList.push_back(interpretor);
		}
		it++;
	}

	std::list<HTTPLocationInterpretor> &listToCheck = possibleLocationList;

	std::list<HTTPLocationInterpretor>::iterator it_listToCheck = listToCheck.begin();
	std::list<HTTPLocationInterpretor>::iterator ite_listToCheck = listToCheck.end();

	std::list<HTTPLocationInterpretor> loc;
	loc.push_back(*it_listToCheck);

	while (it_listToCheck != ite_listToCheck)													
	{																								
		if (it_listToCheck->start().size() > loc.begin()->start().size())							
		{																							
			loc.pop_back();																			
			loc.push_back(*it_listToCheck);															
		}																							
		it_listToCheck++;																			
	}																								
	it_listToCheck = possibleLocationList.begin();
	HTTPLocationInterpretor &bestLocation = *(loc.begin());
	location(bestLocation.locationBlock());
	
	return (*this);
}
