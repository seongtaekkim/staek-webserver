#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <sstream>
#include <iomanip>

class Base {
public:
    static const std::string DECIMAL;
    static const std::string HEX;
private:
    Base(const Base& other);
    Base& operator=(const Base& other);
public:
    Base(void);
    ~Base(void);
    template <typename T>
    static T convert(std::string str, const std::string base) {
        int		length;
        int		result;
        int		sign;

        sign = 1;
        result = 0;
        length = base.size();
        std::string::iterator bit = str.begin();
        for (std::string::iterator i = bit ; i != str.end() ; ++i) {
            if ((*i) == '+' || (*i) == '-') {
                if ((*i) == '-')
                    sign *= -1;
                continue ;
            }
            if (getBase(*i, base) > -1) {
                result = result * length;
                result = result + getBase(*i, base);
            }
            else
                break ;
        }
        return (T(result * sign));
    }
	template<typename T>
	inline static std::string
	toString(const T &t, int base) {
		std::stringstream stream;
		stream << std::setbase(base) << t;
		return (stream.str());
	}
    static int getBase(char c, std::string base);
};

#endif
