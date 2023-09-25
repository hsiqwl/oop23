#ifndef DIALOGUE_LOGICELEMENT_H
#define DIALOGUE_LOGICELEMENT_H
#include <clamp/clamp.h>
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
        static const int logic_element_arr_max_size = 50;
        unsigned int curr_size;
        Clamp arr[logic_element_arr_max_size];
    public:
        LogicElement(unsigned int num_of_out, unsigned num_of_in);

        LogicElement(Clamp array[], unsigned int arr_len);

        LogicElement &reset_signals(signal[], unsigned int);

        LogicElement &add_clamp(Clamp &);

        void operator>>(LogicElement &);

        Clamp &operator[](unsigned);

    };

}


#endif //DIALOGUE_LOGICELEMENT_H
