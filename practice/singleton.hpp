#ifndef SINGLE_HPP
#define SINGLE_HPP

//https://vallista.tistory.com/entry/1-Singleton-Pattern-in-C
class LocalStaticSingleton
{
private:
    LocalStaticSingleton();
    LocalStaticSingleton(const LocalStaticSingleton& other);
    ~LocalStaticSingleton();
	int test;
 
public:
    static LocalStaticSingleton* GetInstance() {
        static LocalStaticSingleton ins;
        return &ins;
    }
	int inc();
};

#endif