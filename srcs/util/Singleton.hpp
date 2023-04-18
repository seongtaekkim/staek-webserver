#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/**
 * @brief singleton
 * @details Singleton을 상속 후, instance 함수를 직접호출하여 싱글톤관리를 할 수 있다.
 * @author seongtki
 * @date 2023.03.26
 */
template<typename T>
class Singleton {
public:
    static T& instance(void) {
		static T _s_instance;
        return (_s_instance);
    }
};

#endif