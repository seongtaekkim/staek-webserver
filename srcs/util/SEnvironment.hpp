#ifndef SENVIRONMENT_HPP
#define SENVIRONMENT_HPP

#include <map>

/**
 * @brief 환경변수 관리
 * @details os 환경변수 및 CGI 등의 사용자 환경변수 관리 객체
 * @author seongtki
 * @date 2023.03.25
 */
class SEnvironment {
private:
	typedef std::map<std::string, std::string>	EnvMap;
	EnvMap										_storage;
	static SEnvironment							_s_env;
public:
	SEnvironment(void);
	SEnvironment(EnvMap map);
	SEnvironment(const SEnvironment& other);
	SEnvironment& operator=(const SEnvironment& other);
	~SEnvironment(void);

public:
	static void setEnv(char **env);
	static SEnvironment& getEnv(void);
	char** envToEnvp(void);
	void setProperty(const std::string& key, const std::string& value);
};

#endif