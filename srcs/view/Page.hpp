#ifndef Page_HPP
#define Page_HPP

#include <string>
#include "../util/Singleton.hpp"

class Page : public Singleton<Page> {
	private:
		Page(const Page& other);
		Page& operator=(const Page& other);
	public:
		Page(void);
		virtual ~Page(void);
		const std::string& resolve(const HTTPStatus::StateType& httpStatus);
};

#endif
