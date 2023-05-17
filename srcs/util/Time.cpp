#include "Time.hpp"

Time::Time(void) : _timeval() {}

Time::Time(Tv timeval) : _timeval(timeval) {}

Time::Time(const Time& other) {
	this->_timeval = other._timeval;
}

Time& Time::operator=(const Time& other) {
	if (this != &other) {
		this->_timeval = other._timeval;
	}
	return (*this);
}

Time::~Time(void) {}


Time Time::NOW(void) {
	struct timeval mytime;

    if (::gettimeofday(&mytime, NULL) == -1)
		throw IOException("gettimeofday error : ", errno);

    return (Time(mytime));
}

std::string Time::format(const char* str) {
	char tmbuf[40];

	Tm *time = ::localtime(&this->_timeval.tv_sec);
	::strftime(tmbuf, sizeof(tmbuf), str, time);
	return (std::string(tmbuf));
}

unsigned long Time::currentSecond(void) {
	struct timeval val;
	if (::gettimeofday(&val, NULL) == -1)
		return (0);
	return (val.tv_sec);
}
