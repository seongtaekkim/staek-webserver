#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class Singleton {
public:
    static T& instance(void) {
		static T _s_instance;
        return (_s_instance);
    }
};

#endif