#include "../test_unit.hpp"
#include "../../srcs/http/response/HTTPState.hpp"
#include "../../srcs/http/response/StatusLine.hpp"
#include <iostream>

/*
	enum을 인자로 넣는 형태는 사용자 오류를 발생시키기 쉽다.
	호출형태로 만드는것이 베스트이지만, 실력이슈로 일단 이렇게..
	예외처리를 할 수 있는지는 체크해보자.
	-> HTTPStatus::CONTINUE 가 현재 enum 인데, 이를 static class 타입으로 고정시키면 될 거 같다.


	 -> pair 는 first, second 를 호출해야하기때문에 class를 만들어서 key, value 등으로 호출하게 만들자.
*/
CASE("statusline==================", "test1")
{	
	ASSERT(StatusLine(HTTPStatus::STATE[HTTPStatus::CONTINUE]).response() == "HTTP/1.1 100 Continue");
	return (0);
}

CASE("status==================", "test1")
{	
	ASSERT(HTTPStatus::STATE[HTTPStatus::CONTINUE].first == 100);
	ASSERT(HTTPStatus::STATE[HTTPStatus::CONTINUE].second == "Continue");
	return (0);
}