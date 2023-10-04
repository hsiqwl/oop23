#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H
#include "clamp/clamp.h"
#include <exception>
#include <string>
#include <compare>
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

        [[nodiscard]] size_t get_curr_size() const {return curr_size;};

        [[nodiscard]] size_t get_max_size() const {return max_size;};

        [[nodiscard]] size_t get_num_of_in() const;

        [[nodiscard]] size_t get_num_of_out() const;

        LogicElement(LogicElement&&) noexcept;

        LogicElement &reset_signals(signal*, size_t);

        LogicElement &add_clamp(Clamp&);

        void operator>>(LogicElement&) const;

        Clamp &operator[](size_t) const;

        LogicElement& operator = (const LogicElement&);

        LogicElement& operator = (LogicElement&&) noexcept;

        std::weak_ordering operator <=>(const LogicElement& obj) const;
    };

};


#endif