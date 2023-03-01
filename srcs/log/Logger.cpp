#include "Logger.hpp"

Logger::~Logger(void) {}

/**
* @brief 인스턴스생성
* @param 로그이름
* @date 2023.03.21
*/
Logger::Logger(const std::string &tag) :
		m_tag(tag)
{}

/**
* @brief 현재시간포맷 + 메세지를 해당 색상에 맞춰 출력한다.
* @return Logger 
* @param color(메세지색상), msg(메세지)
* @date 2023.03.21
*/
void
Logger::log(const std::string& color, std::string msg) {
  time(&this->_time);
  this->time_info = localtime(&this->_time);
  strftime(this->time_buf, sizeof(this->time_buf),
  			"[%Y-%m-%d] %T %a] ", this->time_info);
  std::cout 
  << GREEN << this->time_buf << ORIGIN
            << color << msg << ORIGIN
            << "\n";
}

/**
* @brief 에러레벨 여부확인
* @return bool : true(enable), false(unenable)
* @date 2023.03.21
*/
bool
Logger::isErrorEnabled() const
{
	return (ERROR);
}

/**
* @brief error 레벨인 경우, 해당로그를 출력한다.
* @param msg(메세지)
* @date 2023.03.21
*/
void
Logger::error(const std::string msg) {
	if (isErrorEnabled())  this->log(RED, msg);
}

/**
* @brief warning 레벨인 경우, 해당로그를 출력한다.
* @param msg(메세지)
* @date 2023.03.21
*/void
Logger::warning(const std::string msg) {

}

/**
* @brief info 레벨인 경우, 해당로그를 출력한다.
* @param msg(메세지)
* @date 2023.03.21
*/
void
Logger::info(const std::string msg) {

}

/**
* @brief debug 레벨인 경우, 해당로그를 출력한다.
* @param msg(메세지)
* @date 2023.03.21
*/
void
Logger::debug(const std::string msg) {

}
