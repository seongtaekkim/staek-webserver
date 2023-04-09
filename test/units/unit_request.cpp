#include "../test_unit.hpp"
#include "../../srcs/http/request/Request.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

void	test(std::string __reqString)
{
	Request test(__reqString);

	std::cout << "< Request Line >\n";
	std::cout << test.method() << " " << test.uri() << " " << test.version() << std::endl;
	std::cout << "< Headers > \n";
	const auto& headers = test.headers();
	for (auto it = headers.cbegin(); it != headers.cend(); ++it) {
		std::cout << it->first << ": ";
		const auto& values = it->second;
		for (auto valueIt = values.cbegin(); valueIt != values.cend(); ++valueIt) {
			std::cout << *valueIt;
			if (valueIt != values.cend() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "< Body > \n";
	std::cout << test.body() << std::endl;
}

CASE("unit_request", "test")
{
	// Request Line test
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GETS /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GET/index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test(" /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GET /index.html HTTp/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GET /index.html HTTP/1\r\nHost: www.example.com\r\n\r\n");
	// test("GET /index.html HTTP1.1\r\nHost: www.example.com\r\n\r\n");
	
	// Header test
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com");
	// test("GET /index.html HTTP/1.1\r\nHost:www.example.com\r\n\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost:www.example.com  \r\n\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost:  www.example.com\r\n\r\n");

	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nIf-Modified-Since: Wed, 05 Oct 2022 10:12:43 GMT\r\nIf-None-Match: \"a1b2c3d4e5f6g7h8i9j0k\"\r\n\r\n");
	// test("GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate, br\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nIf-Modified-Since: Wed, 05 Oct 2022 10:12:43 GMT\r\nIf-None-Match: \"a1b2c3d4e5f6g7h8i9j0k\"\r\n\r\n");
	// test("POST /api/user HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0\r\nContent-Type: application/json\r\nContent-Length: 46\r\nConnection: keep-alive\r\n\r\n{\"username\": \"john_doe\", \"password\": \"12345\"}");
	// test("POST /api/users HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: 68\r\n\r\n{\"name\": \"John Doe\", \"email\": \"john.doe@example.com\", \"password\": \"password123\"}");

	// chunked
	// test("POST /example HTTP/1.1\r\nHost: example.com\r\nContent-Type: text/plain\r\nTransfer-Encoding: chunked\r\n\r\n4\r\nthis\r\n5\r\n is a\r\n6\r\n test \r\n0\r\n\r\n");
	
	// multipart
	test("POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Type: multipart/form-data; boundary=----WebKitFormBoundaryabcdefg\r\nContent-Length: <length of request body>\r\n\r\n------WebKitFormBoundaryabcdefg\r\nContent-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\nContent-Type: text/plain\r\n\r\n... contents of example.txt ...\r\n\r\n------WebKitFormBoundaryabcdefg--");
	
	return (0);
}