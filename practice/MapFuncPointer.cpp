#include "MapFuncPointer.hpp"

void Type::LoadFunc() {
	_funcMap["Start"] = &Type::Start;
}
void Type::ActivateFunction()
{
	cin>>buff;
	FuncMapIter _pos = _funcMap.find(buff);
	if(_pos != _funcMap.end())
	{
		FuncPointer func = _pos->second;
		(this->*func)();
	}
}


int main(void) {
	Type t;
	t.LoadFunc();
	t.ActivateFunction();

}