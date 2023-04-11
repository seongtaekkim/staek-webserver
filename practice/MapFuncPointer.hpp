
#include <map>
#include <iostream>
#include <string>
using namespace std;
class Type {

public:
typedef void (Type::*FuncPointer)();
typedef map<std::string, FuncPointer > FuncMap;
typedef map<std::string, FuncPointer>::iterator FuncMapIter;

FuncMap _funcMap;
FuncMapIter _pos;
string buff;

public:
Type(){};
~Type(){};

void LoadFunc();

void ActivateFunction();

private:
void Start(){  std::cout<<"Start function !"<<std::endl;
}
};

