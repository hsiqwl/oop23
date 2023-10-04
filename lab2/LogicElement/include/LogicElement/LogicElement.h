#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H
#include "clamp/clamp.h"
#include <exception>
#include <string>
using namespace clamp_class;

namespace LogicElementClass {

    class LogicElement {
    private:
        static const unsigned int resize_var = 10;
        size_t curr_size;
        size_t max_size;
        Clamp* arr;

        void resize_arr(size_t);

    public:
        LogicElement() = default;

        LogicElement(size_t, size_t);

        LogicElement(Clamp*, size_t);

        LogicElement(const LogicElement&);

        ~LogicElement(){delete[] arr;};

        LogicElement(LogicElement&&) noexcept;

        LogicElement &reset_signals(signal*, size_t);

        LogicElement &add_clamp(Clamp&);

        void operator>>(LogicElement&) const;

        Clamp &operator[](size_t) const;

        LogicElement& operator = (const LogicElement&);

        LogicElement& operator = (LogicElement&&) noexcept;

    };

}


#endif
