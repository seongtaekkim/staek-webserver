#ifndef RESPOSE_HPP
#define RESPOSE_HPP

#include "Common.hpp"

| 2    | _status             | variable | status code와 사유구절(des)/응답본문(body) 저장 |      | private |
| ---- | ------------------- | -------- | ----------------------------------------------- | ---- | ------- |
| 3    | _connection         | variable | connection 정보                                 |      | private |
| 4    | _status_code        | variable | status code                                     |      | private |
| 5    | _status_description | variable | 사유                                            |      | private |
| 6    | _headers            | variable | 송신에 header                                   |      | private |
| 8    | _content            | variable | response body                                   |      |         |

class Response {
private:
	d
public:
	void GET(void);
	void POST(void);
	void DELETE(void);
	void send(void);
}

#endif