#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H
#include <iostream>
#include <limits>
namespace utils{
    template<class T>
    T getNum(std::istream& s, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T number;
        while (true) {
            s >> number;
            if (s.eof())
                throw std::runtime_error("It is EOF, sorry\n");
            else if (s.bad())
                throw std::runtime_error("BAD!\n");
            else if (s.fail() || number < min || number > max) {
                s.clear();
                s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            } else return number;
        }
    }
}

#endif //LAB2_UTILS_H
