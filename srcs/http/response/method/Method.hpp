#ifndef METHOD_HPP
#define METHOD_HPP

#include <iostream>
#include <map>
#include "IMethod.hpp"
#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"

class Method {
public:
	typedef std::map<int, IMethod*> MethodMap;
	static MethodMap METHOD;
private:
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
	enum {
		GET=1,
		POST=2,
		DELETE=3
	};
};

#endif