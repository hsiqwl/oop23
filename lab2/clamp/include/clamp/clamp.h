#ifndef LAB2_CLAMP_H
#define LAB2_CLAMP_H
#include <string>
namespace clamp_class {
    ///Types that an object of a class can take
    enum clamp_type {
        in,
        out
    };
    ///Types of signals that an object can take
    enum signal {
        low,
        high,
        undefined
    };

    ///Clamp is a class that contains three fields fully describing an object
    class Clamp {
    private:
        clamp_type type;
        signal status;
        unsigned short link_num; ///number of other objects to which this object is connected
    public:
        Clamp();

        Clamp(clamp_type, signal, unsigned short);

        explicit  Clamp(clamp_type);

        Clamp& set_type(clamp_type);

        Clamp& set_status(signal);

        Clamp& set_link_num(unsigned short);

        [[nodiscard]] clamp_type get_type() const noexcept;

        [[nodiscard]] signal get_signal() const noexcept;

        [[nodiscard]] int get_link_num() const noexcept;

        void print(std::ostream&) const noexcept;

        Clamp& operator ++ ();

        Clamp& operator -- ();

        Clamp operator ++ (int);

        Clamp operator -- (int);

        void operator >> (Clamp&);

        void operator << (Clamp&);

        void operator ! ();
    };

    std::ostream& operator << (std::ostream& s, Clamp& obj);

}

#endif //LAB2_CLAMP_H
