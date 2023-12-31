#include "SEnvironment.hpp"

SEnvironment SEnvironment::_sEnv;

SEnvironment::SEnvironment(void) : _env() {}

SEnvironment::SEnvironment(EnvMap map) : _env(map) {}

SEnvironment::SEnvironment(const SEnvironment& other) : _env(other._env) {}

SEnvironment& SEnvironment::operator=(const SEnvironment& other) {
	if (this != &other) {
		this->_env = other._env;
	}
	return (*this);
}

SEnvironment::~SEnvironment(void) {}

/**
* @brief os env 세팅
* @param char **env
* @date 2023.03.26
*/
SEnvironment SEnvironment::charToMap(char **env) {
	SEnvironment environment;

	char* key;
	while ((key = *env)) {
		char* equal = std::strchr(key, '=');
		std::string str = key;
		char* value = NULL;
		if (*equal) {
			equal[0] = '\0';
			value = equal + 1; 
		}
		environment.appendOne(str.substr(0, str.find("=")), value);		
		env++;
	}
	return (environment);
}

void SEnvironment::setEnv(char** envp) {
	SEnvironment::_sEnv = SEnvironment::charToMap(envp);
}

SEnvironment::EnvMap& SEnvironment::getMap(void) {
	return (this->_env);
}

SEnvironment& SEnvironment::getEnv(void) {
	return (SEnvironment::_sEnv);
}

/**
* @brief map to char**
* @param char **env
* @date 2023.05.15
*/
char** SEnvironment::mapToChar(void) const {
	char **envp = new char*[this->_env.size() + 1];
	EnvMap::size_type index = 0;	
	for (EnvMap::const_iterator it = this->_env.begin(); it != this->_env.end(); ++it) {
		std::string line = it->first + '=' + it->second;
		envp[index++] = ft::strdup(line.c_str());
	}
	envp[index] = NULL;
	return (envp);
}

int SEnvironment::size(void) const {
	return this->_env.size();
}

/**
* @brief 환경변수 추가
* @param (key, value)
* @date 2023.03.26
*/
void SEnvironment::appendOne(const std::string& key, const std::string& value) {
	EnvMap::iterator it = this->_env.find(key);

	if (it == this->_env.end()) 
		this->_env.insert(std::make_pair(key, value));
	else
		(*it).second = value;
}

std::string SEnvironment::getOne(const std::string& key) {
	EnvMap::iterator it = this->_env.find(key);
	if (it == this->_env.end())
		return (std::string());
	return ((*it).second);
}

bool SEnvironment::hasOne(const std::string& key) {
	if (this->_env.find(key) == this->_env.end())
		return (false);
	return (true);
}