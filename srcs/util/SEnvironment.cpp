#include "SEnvironment.hpp"

SEnvironment::SEnvironment(void) {}
SEnvironment::SEnvironment(EnvMap map) {}
SEnvironment::SEnvironment(const SEnvironment& other) {}
SEnvironment& SEnvironment::operator=(const SEnvironment& other) {}
SEnvironment::~SEnvironment(void) {}

/**
* @brief os env 세팅
* @param char **env
* @date 2023.03.26
*/
void SEnvironment::setEnv(char **env) {
	// map<string, string>
	SEnvironment env;
	// _storage = e;
}

SEnvironment& SEnvironment::getEnv(void) {
	return (SEnvironment::_s_env);
}

/**
* @brief map to char**
* @param char **env
* @date 2023.03.26
*/
char** envToEnvp(void) {

}

/**
* @brief 환경변수 추가
* @param (key, value)
* @date 2023.03.26
*/
void setProperty(const std::string& key, const std::string& value) {
	
}
