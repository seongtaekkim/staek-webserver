#include "Callback.hpp"
#include <iostream>
#include "A.hpp"
#include "B.hpp"

/*
	Callback 예제
	B 생성자 파라메터를 CallBack 객체로 설정하고,
	B 를 생성할 때 인자는 A 객체를 삽입하여 Callback 객체 에 할당한다.
	Callback 객체는 A객체의 기능을 사용할 수 있다.
*/
int main(void) {
	A a;
	B b(a);
	b.dofunc();
	return (0);
}