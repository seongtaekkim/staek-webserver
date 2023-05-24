#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

#include <iostream>
#include <map>

// https://stackoverflow.com/questions/13464325/static-map-initialization
class HTTPStatus {
public:
	typedef std::map<int, std::pair<int, std::string> > StateMap; 
	typedef std::pair<int, std::string>					StateType; 

private:
	std::string	_codeNm;
	int			_code;
	static StateMap init() {
		StateMap state;
		state[HTTPStatus::CONTINUE].first				= HTTPStatus::CONTINUE;
		state[HTTPStatus::CONTINUE].second				= "Continue";
		state[HTTPStatus::SWITCHING_PROTOCOLS].first	= HTTPStatus::SWITCHING_PROTOCOLS;
		state[HTTPStatus::SWITCHING_PROTOCOLS].second	= "Switching Protocols";
		state[HTTPStatus::PROCESSING].first = HTTPStatus::PROCESSING;
		state[HTTPStatus::PROCESSING].second = "Processing";
		state[HTTPStatus::CHECKPOINT].first = HTTPStatus::CHECKPOINT;
		state[HTTPStatus::CHECKPOINT].second = "Checkpoint";
		state[HTTPStatus::OK].first = HTTPStatus::OK;
		state[HTTPStatus::OK].second = "OK";
		state[HTTPStatus::CREATED].first = HTTPStatus::CREATED;
		state[HTTPStatus::CREATED].second = "Created";
		state[HTTPStatus::ACCEPTED].first = HTTPStatus::ACCEPTED;
		state[HTTPStatus::ACCEPTED].second = "Accepted";
		state[HTTPStatus::NON_AUTHORITATIVE_INFORMATION].first = HTTPStatus::NON_AUTHORITATIVE_INFORMATION;
		state[HTTPStatus::NON_AUTHORITATIVE_INFORMATION].second = "Non-Authoritative Information";
		state[HTTPStatus::NO_CONTENT].first = HTTPStatus::NO_CONTENT;
		state[HTTPStatus::NO_CONTENT].second = "No Content";
		state[HTTPStatus::RESET_CONTENT].first = HTTPStatus::RESET_CONTENT;
		state[HTTPStatus::RESET_CONTENT].second = "Reset Content";
		state[HTTPStatus::PARTIAL_CONTENT].first = HTTPStatus::PARTIAL_CONTENT;
		state[HTTPStatus::PARTIAL_CONTENT].second = "Partial Content";
		state[HTTPStatus::MULTI_STATUS].first = HTTPStatus::MULTI_STATUS;
		state[HTTPStatus::MULTI_STATUS].second = "Multi-Status";
		state[HTTPStatus::ALREADY_REPORTED].first = HTTPStatus::ALREADY_REPORTED;
		state[HTTPStatus::ALREADY_REPORTED].second = "Already Reported";
		state[HTTPStatus::IM_USED].first = HTTPStatus::IM_USED;
		state[HTTPStatus::IM_USED].second = "IM Used";
		state[HTTPStatus::MULTIPLE_CHOICES].first = HTTPStatus::MULTIPLE_CHOICES;
		state[HTTPStatus::MULTIPLE_CHOICES].second = "Multiple Choices";
		state[HTTPStatus::MOVED_PERMANENTLY].first = HTTPStatus::MOVED_PERMANENTLY;
		state[HTTPStatus::MOVED_PERMANENTLY].second = "Moved Permanently";
		state[HTTPStatus::FOUND].first = HTTPStatus::FOUND;
		state[HTTPStatus::FOUND].second = "Found";
		state[HTTPStatus::MOVED_TEMPORARILY].first = HTTPStatus::MOVED_TEMPORARILY;
		state[HTTPStatus::MOVED_TEMPORARILY].second = "Moved Temporarily";
		state[HTTPStatus::SEE_OTHER].first = HTTPStatus::SEE_OTHER;
		state[HTTPStatus::SEE_OTHER].second = "See Other";
		state[HTTPStatus::NOT_MODIFIED].first = HTTPStatus::NOT_MODIFIED;
		state[HTTPStatus::NOT_MODIFIED].second = "Not Modified";
		state[HTTPStatus::USE_PROXY].first = HTTPStatus::USE_PROXY;
		state[HTTPStatus::USE_PROXY].second = "Use Proxy";
		state[HTTPStatus::TEMPORARY_REDIRECT].first = HTTPStatus::TEMPORARY_REDIRECT;
		state[HTTPStatus::TEMPORARY_REDIRECT].second = "Temporary Redirect";
		state[HTTPStatus::PERMANENT_REDIRECT].first = HTTPStatus::PERMANENT_REDIRECT;
		state[HTTPStatus::PERMANENT_REDIRECT].second = "Permanent Redirect";
		state[HTTPStatus::BAD_REQUEST].first = HTTPStatus::BAD_REQUEST;
		state[HTTPStatus::BAD_REQUEST].second = "Bad Request";
		state[HTTPStatus::UNAUTHORIZED].first = HTTPStatus::UNAUTHORIZED;
		state[HTTPStatus::UNAUTHORIZED].second = "Unauthorized";
		state[HTTPStatus::PAYMENT_REQUIRED].first = HTTPStatus::PAYMENT_REQUIRED;
		state[HTTPStatus::PAYMENT_REQUIRED].second = "Payment Required";
		state[HTTPStatus::FORBIDDEN].first = HTTPStatus::FORBIDDEN;
		state[HTTPStatus::FORBIDDEN].second = "Forbidden";
		state[HTTPStatus::MOVED_PERMANENTLY].first = HTTPStatus::MOVED_PERMANENTLY;
		state[HTTPStatus::MOVED_PERMANENTLY].second = "Moved Permanently";
		state[HTTPStatus::FOUND].first = HTTPStatus::FOUND;
		state[HTTPStatus::FOUND].second = "Found";
		state[HTTPStatus::MOVED_TEMPORARILY].first = HTTPStatus::MOVED_TEMPORARILY;
		state[HTTPStatus::MOVED_TEMPORARILY].second = "Moved Temporarily";
		state[HTTPStatus::SEE_OTHER].first = HTTPStatus::SEE_OTHER;
		state[HTTPStatus::SEE_OTHER].second = "See Other";
		state[HTTPStatus::NOT_MODIFIED].first = HTTPStatus::NOT_MODIFIED;
		state[HTTPStatus::NOT_MODIFIED].second = "Not Modified";
		state[HTTPStatus::USE_PROXY].first = HTTPStatus::USE_PROXY;
		state[HTTPStatus::USE_PROXY].second = "Use Proxy";
		state[HTTPStatus::TEMPORARY_REDIRECT].first = HTTPStatus::TEMPORARY_REDIRECT;
		state[HTTPStatus::TEMPORARY_REDIRECT].second = "Temporary Redirect";
		state[HTTPStatus::PERMANENT_REDIRECT].first = HTTPStatus::PERMANENT_REDIRECT;
		state[HTTPStatus::PERMANENT_REDIRECT].second = "Permanent Redirect";
		state[HTTPStatus::BAD_REQUEST].first = HTTPStatus::BAD_REQUEST;
		state[HTTPStatus::BAD_REQUEST].second = "Bad Request";
		state[HTTPStatus::UNAUTHORIZED].first = HTTPStatus::UNAUTHORIZED;
		state[HTTPStatus::UNAUTHORIZED].second = "Unauthorized";
		state[HTTPStatus::PAYMENT_REQUIRED].first = HTTPStatus::PAYMENT_REQUIRED;
		state[HTTPStatus::PAYMENT_REQUIRED].second = "Payment Required";
		state[HTTPStatus::FORBIDDEN].first = HTTPStatus::FORBIDDEN;
		state[HTTPStatus::FORBIDDEN].second = "Forbidden";
		state[HTTPStatus::NOT_FOUND].first = HTTPStatus::NOT_FOUND;
		state[HTTPStatus::NOT_FOUND].second = "Not Found";
		state[HTTPStatus::METHOD_NOT_ALLOWED].first = HTTPStatus::METHOD_NOT_ALLOWED;
		state[HTTPStatus::METHOD_NOT_ALLOWED].second = "Method Not Allowed";
		state[HTTPStatus::NOT_ACCEPTABLE].first = HTTPStatus::NOT_ACCEPTABLE;
		state[HTTPStatus::NOT_ACCEPTABLE].second = "Not Acceptable";
		state[HTTPStatus::PROXY_AUTHENTICATION_REQUIRED].first = HTTPStatus::PROXY_AUTHENTICATION_REQUIRED;
		state[HTTPStatus::PROXY_AUTHENTICATION_REQUIRED].second = "Proxy Authentication Required";
		state[HTTPStatus::REQUEST_TIMEOUT].first = HTTPStatus::REQUEST_TIMEOUT;
		state[HTTPStatus::REQUEST_TIMEOUT].second = "Request Timeout";
		state[HTTPStatus::CONFLICT].first = HTTPStatus::CONFLICT;
		state[HTTPStatus::CONFLICT].second = "Conflict";
		state[HTTPStatus::GONE].first = HTTPStatus::GONE;
		state[HTTPStatus::GONE].second = "Gone";
		state[HTTPStatus::LENGTH_REQUIRED].first = HTTPStatus::LENGTH_REQUIRED;
		state[HTTPStatus::LENGTH_REQUIRED].second = "Length Required";
		state[HTTPStatus::PRECONDITION_FAILED].first = HTTPStatus::PRECONDITION_FAILED;
		state[HTTPStatus::PRECONDITION_FAILED].second = "Precondition Failed";
		state[HTTPStatus::PAYLOAD_TOO_LARGE].first = HTTPStatus::PAYLOAD_TOO_LARGE;
		state[HTTPStatus::PAYLOAD_TOO_LARGE].second = "Payload Too Large";
		state[HTTPStatus::REQUEST_ENTITY_TOO_LARGE].first = HTTPStatus::REQUEST_ENTITY_TOO_LARGE;
		state[HTTPStatus::REQUEST_ENTITY_TOO_LARGE].second = "Request Entity Too Large";
		state[HTTPStatus::URI_TOO_LONG].first = HTTPStatus::URI_TOO_LONG;
		state[HTTPStatus::URI_TOO_LONG].second = "URI Too Long";
		state[HTTPStatus::REQUEST_URI_TOO_LONG].first = HTTPStatus::REQUEST_URI_TOO_LONG;
		state[HTTPStatus::REQUEST_URI_TOO_LONG].second = "Request-URI Too Long";
		state[HTTPStatus::UNSUPPORTED_MEDIA_TYPE].first = HTTPStatus::UNSUPPORTED_MEDIA_TYPE;
		state[HTTPStatus::UNSUPPORTED_MEDIA_TYPE].second = "Unsupported Media Type";
		state[HTTPStatus::REQUESTED_RANGE_NOT_SATISFIABLE].first = HTTPStatus::REQUESTED_RANGE_NOT_SATISFIABLE;
		state[HTTPStatus::REQUESTED_RANGE_NOT_SATISFIABLE].second = "Requested range not satisfiable";
		state[HTTPStatus::EXPECTATION_FAILED].first = HTTPStatus::EXPECTATION_FAILED;
		state[HTTPStatus::EXPECTATION_FAILED].second = "Expectation Failed";
		state[HTTPStatus::I_AM_A_TEAPOT].first = HTTPStatus::I_AM_A_TEAPOT;
		state[HTTPStatus::I_AM_A_TEAPOT].second = "I'm a teapot";
		state[HTTPStatus::INSUFFICIENT_SPACE_ON_RESOURCE].first = HTTPStatus::INSUFFICIENT_SPACE_ON_RESOURCE;
		state[HTTPStatus::INSUFFICIENT_SPACE_ON_RESOURCE].second = "Insufficient Space On Resource";
		state[HTTPStatus::METHOD_FAILURE].first = HTTPStatus::METHOD_FAILURE;
		state[HTTPStatus::METHOD_FAILURE].second = "Method Failure";
		state[HTTPStatus::DESTINATION_LOCKED].first = HTTPStatus::DESTINATION_LOCKED;
		state[HTTPStatus::DESTINATION_LOCKED].second = "Destination Locked";
		state[HTTPStatus::UNPROCESSABLE_ENTITY].first = HTTPStatus::UNPROCESSABLE_ENTITY;
		state[HTTPStatus::UNPROCESSABLE_ENTITY].second = "Unprocessable Entity";
		state[HTTPStatus::LOCKED].first = HTTPStatus::LOCKED;
		state[HTTPStatus::LOCKED].second = "Locked";
		state[HTTPStatus::FAILED_DEPENDENCY].first = HTTPStatus::FAILED_DEPENDENCY;
		state[HTTPStatus::FAILED_DEPENDENCY].second = "Failed Dependency";
		state[HTTPStatus::TOO_EARLY].first = HTTPStatus::TOO_EARLY;
		state[HTTPStatus::TOO_EARLY].second = "Too Early";
		state[HTTPStatus::PRECONDITION_REQUIRED].first = HTTPStatus::PRECONDITION_REQUIRED;
		state[HTTPStatus::PRECONDITION_REQUIRED].second = "Precondition Required";
		state[HTTPStatus::UPGRADE_REQUIRED].first = HTTPStatus::UPGRADE_REQUIRED;
		state[HTTPStatus::UPGRADE_REQUIRED].second = "Upgrade Required";
		state[HTTPStatus::TOO_MANY_REQUESTS].first = HTTPStatus::TOO_MANY_REQUESTS;
		state[HTTPStatus::TOO_MANY_REQUESTS].second = "Too Many Requests";
		state[HTTPStatus::REQUEST_HEADER_FIELDS_TOO_LARGE].first = HTTPStatus::REQUEST_HEADER_FIELDS_TOO_LARGE;
		state[HTTPStatus::REQUEST_HEADER_FIELDS_TOO_LARGE].second = "Request Header Fields Too Large";
		state[HTTPStatus::UNAVAILABLE_FOR_LEGAL_REASONS].first = HTTPStatus::UNAVAILABLE_FOR_LEGAL_REASONS;
		state[HTTPStatus::UNAVAILABLE_FOR_LEGAL_REASONS].second = "Unavailable For Legal Reasons";
		state[HTTPStatus::INTERNAL_SERVER_ERROR].first = HTTPStatus::INTERNAL_SERVER_ERROR;
		state[HTTPStatus::INTERNAL_SERVER_ERROR].second = "Internal Server Error";
		state[HTTPStatus::NOT_IMPLEMENTED].first = HTTPStatus::NOT_IMPLEMENTED;
		state[HTTPStatus::NOT_IMPLEMENTED].second = "Not Implemented";
		state[HTTPStatus::BAD_GATEWAY].first = HTTPStatus::BAD_GATEWAY;
		state[HTTPStatus::BAD_GATEWAY].second = "Bad Gateway";
		state[HTTPStatus::SERVICE_UNAVAILABLE].first = HTTPStatus::SERVICE_UNAVAILABLE;
		state[HTTPStatus::SERVICE_UNAVAILABLE].second = "Service Unavailable";
		state[HTTPStatus::GATEWAY_TIMEOUT].first = HTTPStatus::GATEWAY_TIMEOUT;
		state[HTTPStatus::GATEWAY_TIMEOUT].second = "Gateway Timeout";
		state[HTTPStatus::HTTP_VERSION_NOT_SUPPORTED].first = HTTPStatus::HTTP_VERSION_NOT_SUPPORTED;
		state[HTTPStatus::HTTP_VERSION_NOT_SUPPORTED].second = "HTTP Version not supported";
		state[HTTPStatus::VARIANT_ALSO_NEGOTIATES].first = HTTPStatus::VARIANT_ALSO_NEGOTIATES;
		state[HTTPStatus::VARIANT_ALSO_NEGOTIATES].second = "Variant Also Negotiates";
		state[HTTPStatus::INSUFFICIENT_STORAGE].first = HTTPStatus::INSUFFICIENT_STORAGE;
		state[HTTPStatus::INSUFFICIENT_STORAGE].second = "Insufficient Storage";
		state[HTTPStatus::LOOP_DETECTED].first = HTTPStatus::LOOP_DETECTED;
		state[HTTPStatus::LOOP_DETECTED].second = "Loop Detected";
		state[HTTPStatus::BANDWIDTH_LIMIT_EXCEEDED].first = HTTPStatus::BANDWIDTH_LIMIT_EXCEEDED;
		state[HTTPStatus::BANDWIDTH_LIMIT_EXCEEDED].second = "Bandwidth Limit Exceeded";
		state[HTTPStatus::NOT_EXTENDED].first = HTTPStatus::NOT_EXTENDED;
		state[HTTPStatus::NOT_EXTENDED].second = "Not Extended";
		return (state);
	}
public:
	HTTPStatus(void);
	HTTPStatus(const HTTPStatus& other);
	HTTPStatus& operator=(const HTTPStatus& other);
	~HTTPStatus(void);
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
};

#endif