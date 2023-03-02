#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @brief webserv의 Exception 최상위 클래스 정의
 * @details webserv의 Exception 최상위 클래스 정의
 * @author seongtki
 * @date 2023.03.22
 */
class Exception : public std::exception {
 private:
  std::string _message;

 public:
  Exception(void);
  Exception(const std::string& errorMessage);
  Exception(const Exception& t);
  Exception& operator=(const Exception& t);
  virtual ~Exception(void) throw();

  const std::string message(void) const;
  virtual const char* what(void) const throw();
};

#endif
