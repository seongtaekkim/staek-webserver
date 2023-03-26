#ifndef CALLBACK_HPP
#define CALLBACK_HPP

class Callback {
public:
	virtual ~Callback();
	virtual bool recv() = 0;
	virtual bool send() = 0 ;	
};

#endif