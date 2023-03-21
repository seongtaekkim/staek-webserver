#include "Logger.hpp"

Logger::Logger(void) {}
Logger::~Logger(void) {}

Logger::Logger(const std::string &tag) :
		m_tag(tag)
{}

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


bool
Logger::isErrorEnabled() const
{
	return (ERROR);
}

void
Logger::error(const std::string msg) {
	if (isErrorEnabled())  this->log(RED, msg);
}
void
Logger::warning(const std::string msg) {

}
void
Logger::info(const std::string msg) {

}
void
Logger::debug(const std::string msg) {

}
