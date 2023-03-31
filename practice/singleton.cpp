#include "single.hpp"
#include <iostream>

LocalStaticSingleton::LocalStaticSingleton() {
	std::cout << "create" << std::endl;
	this->test = 0;
}
LocalStaticSingleton::LocalStaticSingleton(const LocalStaticSingleton& other) {}
LocalStaticSingleton::~LocalStaticSingleton() {}

int LocalStaticSingleton::inc() {
	this->test++;
	return (this->test);
}

int main(void) {
	{
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	}
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	std::cout << LocalStaticSingleton::GetInstance()->inc();
	std::cout << LocalStaticSingleton::GetInstance()->inc();
}