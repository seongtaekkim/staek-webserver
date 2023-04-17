



## 진행상황



config

- root block
- server block
- mime types
- cgi block





- [ ] parser

- [ ] reader
  - [ ] file read
  - [ ] ​	

​		

- [ ] server-client connect 생명주기 관리

- [ ] kqueue manage

- [ ] request

- [ ] response

- [ ] cgi

- [ ] cookie

- [ ] util
  - [ ] File
  - [ ] FileDescriptor
  - [ ] Time
  - [ ] URI
  - [ ] Envirenment

ㅇ



http version











# 설계

main -> webserv 생성 -> 



### Webserv

| No   | name     | type     | desc                | domain      | access  |
| ---- | -------- | -------- | ------------------- | ----------- | ------- |
| 1    | _servers | variable | server 객체들 (1개) | std::string | private |
| 2    | _config  | variable | configuration 결과  | Config?     | private |
| 3    | _max_fd  | variable | max fd              | int         | private |



### Listen

| No   | name  | type     | desc | domain      | access  |
| ---- | ----- | -------- | ---- | ----------- | ------- |
| 1    | _ip   | variable | ip   | std::string | private |
| 2    | _port | variable | port | uint32_t    | private |



### configuration

| No   | name              | type     | desc                   | domain      | access  |
| ---- | ----------------- | -------- | ---------------------- | ----------- | ------- |
| 1    | _software_version | variable | 웹서버 소프트웨어 버전 | string      | private |
| 2    | _http_version     | variable | HTTP 프로토콜 버전     | string(1.1) | private |
| 3    | _cgi_version      | variable | CGI 사양               | string(1.1) | private |
| 4    | _env              | variable | 환경변수               | char**      | private |



### ServerContext

- server 정보

| No   | name         | type   | desc | domain | access  |
| ---- | ------------ | ------ | ---- | ------ | ------- |
| 1    | _tokens      | tokens |      |        | private |
| 2    | _config      |        |      |        | private |
| 3    | _uri         |        |      |        | private |
| 4    | _root        |        |      |        | private |
| 5    | _upload      |        |      |        | private |
| 6    | _cgi_bin     |        |      |        | private |
| 7    | _listens     |        |      |        | private |
| 8    | _methods     |        |      |        | private |
| 9    | _locations   |        |      |        | private |
| 10   | _error_pages |        |      |        | private |
|      |              |        |      |        |         |
|      |              |        |      |        |         |



### Server

- HTTP 프로토콜에 따라 Request 수신,  Response 생성, 전송

| No   | name           | type                     | desc | domain | access  |
| ---- | -------------- | ------------------------ | ---- | ------ | ------- |
| 1    | _fds           | fd set                   |      |        | private |
| 2    | _max_fd        | int                      |      |        | private |
| 3    | _read_fds      | int                      |      |        | private |
| 4    | _write_fds     | int                      |      |        | private |
| 5    | _serv_contexts | std::vector<ServContext> |      |        | private |
| 6    | _servers       | std::map<int, Listen>    | 1개  |        | private |
| 7    | _clients       | Clients                  |      |        | private |
|      |                |                          |      |        |         |

### Location

- Configuration 파일의 Location Block 안 정보들을 저장한다. Server 객체의 멤버 변수로 사용된다.

| No   | name             | type     | desc                   | domain            | access  |
| ---- | ---------------- | -------- | ---------------------- | ----------------- | ------- |
| 1    | _uri             | variable | uri 정보               | string            | private |
| 2    | _root_path       | variable | 웹서버 소프트웨어 이름 | string            | private |
| 3    | _method          | variable | 메소드                 | string set        | private |
| 4    | _auth_basic_file | variable | 인증 파일 데이터       | string:string map | private |
| 5    | _cgi             | variable | (허용) cgi 확장자      | string set        | private |



### Connection

| No   | name         | type | desc            | domain | access  |
| ---- | ------------ | ---- | --------------- | ------ | ------- |
| 1    | _fd          | data | 클라이언트 fd   |        | private |
| 3    | _client_ip   | data | 클라이언트 ip   |        | private |
| 4    | _client_port | data | 클라이언트 port |        | private |



### Request

| No   | name | type | desc | domain | access |
| ---- | ---- | ---- | ---- | ------ | ------ |
|      |      |      |      |        |        |
|      |      |      |      |        |        |



### Response

- Response 정보들을 저장한다. 한번에 몰아서 전송하며, 전송 순서 보장을 위해 서버 객체에 Queue 자료구조로 저장된다.

| No   | name                | type     | desc                                                         | domain | access  |
| ---- | ------------------- | -------- | ------------------------------------------------------------ | ------ | ------- |
| 2    | _status             | variable | status code와 사유(desc)/<br />응답본문(body) 저장 => 변경필요 |        | private |
| 3    | _connection         | variable | connection 정보 => Listen 명칭 변경 검토 필요                |        | private |
| 4    | _status_code        | variable | status code                                                  |        | private |
| 5    | _status_description | variable | 사유                                                         |        | private |
| 6    | _headers            | variable | 송신에 header                                                |        | private |
| 8    | _content            | variable | response body                                                |        | private |
| 9    | get                 | method   |                                                              |        | public  |
| 10   | post                | method   |                                                              |        | public  |
| 11   | delete              | method   |                                                              |        | public  |
| 12   | send                | method   |                                                              |        | public  |

### Mimes

| No   | name   | type     | desc  | domain                                           | access  |
| ---- | ------ | -------- | ----- | ------------------------------------------------ | ------- |
| 1    | _mines | variable | mines | map<string, string><br />{".html" : "text/html"} | private |

### Parser

### File

- 파일 객체 관리

| No   | name       | type     | desc            | domain      | access  |
| ---- | ---------- | -------- | --------------- | ----------- | ------- |
| 1    | _fd        | variable | file descriptor | int         | private |
| 2    | _name      | variable | 파일 이름       | str::string | private |
| 3    | _extension | variable | 확장자          | str::string | private |
| 4    | _path      | variable | file path       | str::string | private |
|      |            |          |                 |             |         |

### WebservException : public std::exception

- webserv custom exception

| No   | name          | type     | desc                  | domain      | access  |
| ---- | ------------- | -------- | --------------------- | ----------- | ------- |
| 1    | _errorMessage | variable | catched error message | str::string | private |
| 2    |               |          |                       |             |         |
|      |               |          |                       |             |         |

### StateCode

### Master

### Worker

only one



### Log

| No   | name     | type     | desc                     | domain      | access  |
| ---- | -------- | -------- | ------------------------ | ----------- | ------- |
| 1    | _tag     | variable | log class name           | str::string | private |
| 2    | _time    | variable | log datetime             | time_t      | private |
| 3    | time_buf | variable | datetime format variable | char[40]    | private |
| 4    | error    | method   | error level log show     | show        | public  |
|      |          |          |                          |             |         |
|      |          |          |                          |             |         |
|      |          |          |                          |             |         |





### CGI

| No   | name      | type     | desc       | domain      | access  |
| ---- | --------- | -------- | ---------- | ----------- | ------- |
| 1    | _envp     | variable | 환경변수   | char **     | private |
| 2    | _cgi_exec | variable | 실행파일명 | std::string | private |
|      |           |          |            |             |         |
|      |           |          |            |             |         |



### Cookie











# 개발



## 코드 컨밴션

**함수**

/**
\* @brief 함수의 설명
\* @date 함수 업데이트 날짜
\* @return 리턴값에 대한설명
\* @param 함수의 인자 설명
*/

**클래스 주석**

/**

*@brief 간략

*@details 상세

*@author Name, Name@tistory.com

*@date 2019-06-09

*@version 0.0.1

*/



### git 

refactor : 

fix : 

feat : 





### 클래스 명명

static class : 	 SClassname

Interface : 		IClassname

Abstract class : Aclassname

class : 				Classname







### callback

https://codereader37.tistory.com/160



### 소켓 recv send

https://sunyzero.tistory.com/167





|       |                       |
| ----- | --------------------- |
| SHTTP | sstream사용해도 되나? |







filter

before mid after 를 통해 바디를 쌓는다.







# 테스트



