#ifndef TIME_HPP
#define TIME_HPP


#include <ctime>
#include <stddef.h>
#include <string>
#include <sys/time.h>
#include <sys/errno.h>
#include "../exception/IOException.hpp"

//https://www.joinc.co.kr/w/man/2/gettimeofday
//https://onecellboy.tistory.com/176
//https://ko.wikipedia.org/wiki/%EA%B7%B8%EB%A6%AC%EB%8B%88%EC%B9%98_%ED%8F%89%EA%B7%A0%EC%8B%9C
// default : 그라나치 1970.1.1시 + 9시(서울) => Thu, 01 Jan 1970 09:00:00 GMT
class Time {
public:
	typedef struct tm		Tm;
	typedef struct timeval	Tv;
	typedef struct timespec Ts;

private:
	Tv	_timeval;
	Tm	_time;
	Ts	_timespac;
public:
	Time(void);
	Time(Tv timeval);
	Time(Tm time);
	Time(Ts timespac);
	Time(const Time& other);
	Time& operator=(const Time& other);
	~Time(void);
	Tm longToTime();
	std::string format(const char* str);
	std::string formatTimeSpec(const char* str);

public:
	static Time NOW(void);
	static unsigned long currentSecond(void);

};

#endif