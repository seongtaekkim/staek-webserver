#ifndef METHOD_HPP
#define METHOD_HPP

#include <iostream>
#include <map>
#include "IMethod.hpp"
#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"
#include "../make/MethodMaker.hpp"

class MethodMaker;

class Method {
public:
	typedef std::map<int, IMethod*> MethodMap;
	static MethodMap METHOD;
	enum { GET, POST, DELETE };
private:
	Delete del;
	MethodMaker* _maker; // 인터페이스는 포인터 혹은 레퍼런스로 정의해야 한다.
	static MethodMap init() {
		MethodMap map;
		map[GET] = Get::instance();
		map[POST] = Post::instance();
		map[DELETE] = Delete::instance();
		Get::instance()->setHasBody(false);
		Post::instance()->setHasBody(true);
		Delete::instance()->setHasBody(false);
		return (map);
	}
	Method(const Method& other);
	Method& operator=(const Method& other);
public:
	Method(void);
	~Method(void);
	// MethodMaker* getMaker(void);

};

#endif