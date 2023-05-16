#ifndef SENVIRONMENT_HPP
#define SENVIRONMENT_HPP

#include <map>
#include "Common.hpp"
#include <iostream>

/**
 * @brief 환경변수 관리
 * @details os 환경변수 및 CGI 등의 사용자 환경변수 관리 객체
 * 			_sEnv : os 환경변수 저장
 * 			_env  : 추가 환경변수 관리변수
 * @author seongtki
 * @date 2023.03.25
 */
class SEnvironment {
public:
	typedef std::map<std::string, std::string>	EnvMap;
private:
	EnvMap										_env;
	static SEnvironment							_sEnv;
public:
	SEnvironment(void);
	SEnvironment(EnvMap map);
	SEnvironment(const SEnvironment& other);
	SEnvironment& operator=(const SEnvironment& other);
	~SEnvironment(void);

public:
	static SEnvironment charToMap(char **env);
	static void setEnv(char** envp);
	static SEnvironment& getEnv(void);
	SEnvironment::EnvMap& getMap(void);
	char** mapToChar(void) const;
	bool hasOne(const std::string& key);
	void appendOne(const std::string& key, const std::string& value);
	std::string getOne(const std::string& key);
	int size(void) const;
};



#endif