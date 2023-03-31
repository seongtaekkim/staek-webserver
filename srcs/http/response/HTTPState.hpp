#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

#include <iostream>
#include <map>

// https://stackoverflow.com/questions/13464325/static-map-initialization
class HTTPStatus {
public:
	typedef std::map<int, std::string> StateMap; 

private:
	std::string	_codeNm;
	int			_code;
	HTTPStatus(const HTTPStatus& other);
	static StateMap init() {
		StateMap state;
		state[HTTPStatus::CONTINUE] = "Continue";
		state[HTTPStatus::SWITCHING_PROTOCOLS] = "Switching Protocols";
		state[HTTPStatus::PROCESSING] = "Processing";
		state[HTTPStatus::CHECKPOINT] = "Checkpoint";
		state[HTTPStatus::OK] = "OK";
		state[HTTPStatus::CREATED] = "Created";
		state[HTTPStatus::ACCEPTED] = "Accepted";
		state[HTTPStatus::NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
		state[HTTPStatus::NO_CONTENT] = "No Content";
		state[HTTPStatus::RESET_CONTENT] = "Reset Content";
		state[HTTPStatus::PARTIAL_CONTENT] = "Partial Content";
		state[HTTPStatus::MULTI_STATUS] = "Multi-Status";
		state[HTTPStatus::ALREADY_REPORTED] = "Already Reported";
		state[HTTPStatus::IM_USED] = "IM Used";
		state[HTTPStatus::MULTIPLE_CHOICES] = "Multiple Choices";
		state[HTTPStatus::MOVED_PERMANENTLY] = "Moved Permanently";
		state[HTTPStatus::FOUND] = "Found";
		state[HTTPStatus::MOVED_TEMPORARILY] = "Moved Temporarily";
		state[HTTPStatus::SEE_OTHER] = "See Other";
		state[HTTPStatus::NOT_MODIFIED] = "Not Modified";
		state[HTTPStatus::USE_PROXY] = "Use Proxy";
		state[HTTPStatus::TEMPORARY_REDIRECT] = "Temporary Redirect";
		state[HTTPStatus::PERMANENT_REDIRECT] = "Permanent Redirect";
		state[HTTPStatus::BAD_REQUEST] = "Bad Request";
		state[HTTPStatus::UNAUTHORIZED] = "Unauthorized";
		state[HTTPStatus::PAYMENT_REQUIRED] = "Payment Required";
		state[HTTPStatus::FORBIDDEN] = "Forbidden";
		state[HTTPStatus::NOT_FOUND] = "Not Found";
		state[HTTPStatus::METHOD_NOT_ALLOWED] = "Method Not Allowed";
		state[HTTPStatus::NOT_ACCEPTABLE] = "Not Acceptable";
		state[HTTPStatus::PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
		state[HTTPStatus::REQUEST_TIMEOUT] = "Request Timeout";
		state[HTTPStatus::CONFLICT] = "Conflict";
		state[HTTPStatus::GONE] = "Gone";
		state[HTTPStatus::LENGTH_REQUIRED] = "Length Required";
		state[HTTPStatus::PRECONDITION_FAILED] = "Precondition Failed";
		state[HTTPStatus::PAYLOAD_TOO_LARGE] = "Payload Too Large";
		state[HTTPStatus::REQUEST_ENTITY_TOO_LARGE] = "Request Entity Too Large";
		state[HTTPStatus::URI_TOO_LONG] = "URI Too Long";
		state[HTTPStatus::REQUEST_URI_TOO_LONG] = "Request-URI Too Long";
		state[HTTPStatus::UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
		state[HTTPStatus::REQUESTED_RANGE_NOT_SATISFIABLE] = "Requested range not satisfiable";
		state[HTTPStatus::EXPECTATION_FAILED] = "Expectation Failed";
		state[HTTPStatus::I_AM_A_TEAPOT] = "I'm a teapot";
		state[HTTPStatus::INSUFFICIENT_SPACE_ON_RESOURCE] = "Insufficient Space On Resource";
		state[HTTPStatus::METHOD_FAILURE] = "Method Failure";
		state[HTTPStatus::DESTINATION_LOCKED] = "Destination Locked";
		state[HTTPStatus::UNPROCESSABLE_ENTITY] = "Unprocessable Entity";
		state[HTTPStatus::LOCKED] = "Locked";
		state[HTTPStatus::FAILED_DEPENDENCY] = "Failed Dependency";
		state[HTTPStatus::TOO_EARLY] = "Too Early";
		state[HTTPStatus::UPGRADE_REQUIRED] = "Upgrade Required";
		state[HTTPStatus::PRECONDITION_REQUIRED] = "Precondition Required";
		state[HTTPStatus::TOO_MANY_REQUESTS] = "Too Many Requests";
		state[HTTPStatus::REQUEST_HEADER_FIELDS_TOO_LARGE] = "Request Header Fields Too Large";
		state[HTTPStatus::UNAVAILABLE_FOR_LEGAL_REASONS] = "Unavailable For Legal Reasons";
		state[HTTPStatus::INTERNAL_SERVER_ERROR] = "Internal Server Error";
		state[HTTPStatus::NOT_IMPLEMENTED] = "Not Implemented";
		state[HTTPStatus::BAD_GATEWAY] = "Bad Gateway";
		state[HTTPStatus::SERVICE_UNAVAILABLE] = "Service Unavailable";
		state[HTTPStatus::GATEWAY_TIMEOUT] = "Gateway Timeout";
		state[HTTPStatus::HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version not supported";
		state[HTTPStatus::VARIANT_ALSO_NEGOTIATES] = "Variant Also Negotiates";
		state[HTTPStatus::INSUFFICIENT_STORAGE] = "Insufficient Storage";
		state[HTTPStatus::LOOP_DETECTED] = "Loop Detected";
		state[HTTPStatus::BANDWIDTH_LIMIT_EXCEEDED] = "Bandwidth Limit Exceeded";
		state[HTTPStatus::NOT_EXTENDED] = "Not Extended";
		return (state);
	}
public:
	HTTPStatus(void);
	HTTPStatus(int code, std::string codeNm);
	static StateMap STATE;
	int code(void) const;
	std::string codeNm(void) const;
	enum  {
		CONTINUE							=100,
		SWITCHING_PROTOCOLS					=101,
		PROCESSING							=102,
		CHECKPOINT							=103,
		OK									=200,
		CREATED								=201,
		ACCEPTED							=202,
		NON_AUTHORITATIVE_INFORMATION		=203,
		NO_CONTENT							=204,
		RESET_CONTENT						=205,
		PARTIAL_CONTENT						=206,
		MULTI_STATUS						=207,
		ALREADY_REPORTED					=208,
		IM_USED								=226,
		MULTIPLE_CHOICES					=300,
		MOVED_PERMANENTLY					=301,
		FOUND								=302,
		MOVED_TEMPORARILY					=302,
		SEE_OTHER							=303,
		NOT_MODIFIED						=304,
		USE_PROXY							=305,
		TEMPORARY_REDIRECT					=307,
		PERMANENT_REDIRECT					=308,
		BAD_REQUEST							=400,
		UNAUTHORIZED						=401,
		PAYMENT_REQUIRED					=402,
		FORBIDDEN							=403,
		NOT_FOUND							=404,
		METHOD_NOT_ALLOWED					=405,
		NOT_ACCEPTABLE						=406,
		PROXY_AUTHENTICATION_REQUIRED		=407,
		REQUEST_TIMEOUT						=408,
		CONFLICT							=409,
		GONE								=410,
		LENGTH_REQUIRED						=411,
		PRECONDITION_FAILED					=412,
		PAYLOAD_TOO_LARGE					=413,
		REQUEST_ENTITY_TOO_LARGE			=413,
		URI_TOO_LONG						=414,
		REQUEST_URI_TOO_LONG				=414,
		UNSUPPORTED_MEDIA_TYPE				=415,
		REQUESTED_RANGE_NOT_SATISFIABLE		=416,
		EXPECTATION_FAILED					=417,
		I_AM_A_TEAPOT						=418,
		INSUFFICIENT_SPACE_ON_RESOURCE		=419,
		METHOD_FAILURE						=420,
		DESTINATION_LOCKED					=421,
		UNPROCESSABLE_ENTITY				=422,
		LOCKED								=423,
		FAILED_DEPENDENCY					=424,
		TOO_EARLY							=425,
		UPGRADE_REQUIRED					=426,
		PRECONDITION_REQUIRED				=428,
		TOO_MANY_REQUESTS					=429,
		REQUEST_HEADER_FIELDS_TOO_LARGE		=431,
		UNAVAILABLE_FOR_LEGAL_REASONS		=451,
		INTERNAL_SERVER_ERROR				=500,
		NOT_IMPLEMENTED						=501,
		BAD_GATEWAY							=502,
		SERVICE_UNAVAILABLE					=503,
		GATEWAY_TIMEOUT						=504,
		HTTP_VERSION_NOT_SUPPORTED			=505,
		VARIANT_ALSO_NEGOTIATES				=506,
		INSUFFICIENT_STORAGE				=507,
		LOOP_DETECTED						=508,
		BANDWIDTH_LIMIT_EXCEEDED			=509,
		NOT_EXTENDED						=510,
	};

	std::string& operator[](const int& k) {
		return (HTTPStatus::STATE[k]);
	}
};

#endif