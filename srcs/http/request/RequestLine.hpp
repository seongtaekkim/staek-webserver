#ifndef REQUESTLINE_HPP
#define REQUESTLINE_HPP
#include <string>

typedef enum s_method
{
  NONE = 0,
  GET,
  POST,
  PUT,
  DELETE,
}	e_method;

/**
 * @brief HTTP 요청 메시지 중 request line를 저장
 * @details method, uri, version을 각각 저장
 * @author chanhyle
 * @date 2023.03.29
 */
struct RequestLine {
	e_method		  _method;
	std::string		_uri;
	float			    _version;
};

#endif