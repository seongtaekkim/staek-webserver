
#ifndef HTTPLOCATIONINTERPRETOR_HPP
#define HTTPLOCATIONINTERPRETOR_HPP

#include "../../config/block/LocationBlock.hpp"
#include <list>
#include <string>

class HTTPLocationInterpretor {
	public:
		enum State
		{
			NOT_STARTED,
			CHECK,
			START,
			END
		};
	
	private:
		State _state;
		std::string _path;
		std::string _start;
		std::string _end;
		std::string _exact;
		const LocationBlock *_locationBlock;

		char _firstChar;
		char _lastChar;
		
	public:
		HTTPLocationInterpretor(void);
		HTTPLocationInterpretor(std::string path, const LocationBlock *locationBlock);
		HTTPLocationInterpretor(const HTTPLocationInterpretor &other);
		
		~HTTPLocationInterpretor();

		HTTPLocationInterpretor& operator=(const HTTPLocationInterpretor &other);

		const std::string& start(void);
		const std::string& end(void);
		const std::string& exact(void);
		const char& firstChar(void);
		const char& lastChar(void);
		void erase();
		void setEnd(std::string end);	
		bool next(char &c);
		void parse(char &c);
		void end(std::string &end);
		const LocationBlock* locationBlock();
};

#endif

