#ifndef DIALOGUE_LOGICELEMENT_H
#define DIALOGUE_LOGICELEMENT_H
#include "clamp/clamp.h"
#include <exception>
#include <string>
using namespace clamp_class;

namespace LogicElementClass {

    class LogicElementException : public std::exception {
    private:
        std::string message;
    public:
        explicit LogicElementException(const std::string &msg) : message{msg} {}

        const std::string &info() { return message; }
    };

    class LogicElement {
    private:
        static const unsigned int resize_var = 10;
        unsigned int curr_size;
        unsigned int max_size;
        Clamp* arr;

        void resize_arr(unsigned int);

    public:
        LogicElement() = default;

        LogicElement(unsigned int, unsigned int);

        LogicElement(Clamp*, unsigned int);

        LogicElement(const LogicElement&);

        ~LogicElement(){delete[] arr};

        LogicElement(LogicElement&&) noexcept;

        LogicElement &reset_signals(signal*, unsigned int);

        LogicElement &add_clamp(Clamp&);

        void operator>>(LogicElement&);

        Clamp &operator[](unsigned);

        LogicElement& operator = (const LogicElement&);

        LogicElement& operator = (LogicElement&&) noexcept;

    };

}


#endif //DIALOGUE_LOGICELEMENT_H
