#ifndef LAB2_CLAMP_H
#define LAB2_CLAMP_H
#include <string>
namespace clamp_class {
    enum clamp_type {
        in, out
    };
    enum signal {
        low, high, undefined
    };

    class clamp_exception: public std::exception{
    private:
        std::string message;
    public:
        explicit clamp_exception(const std::string& msg){
            message = msg;
        }
        std::string& exception_info(){
            return message;
        }
    };

    class Clamp {
    private:
        clamp_type type;
        signal status;
        unsigned short link_num;
    public:
        Clamp();

        Clamp(clamp_type, signal, unsigned short);

        explicit Clamp(clamp_type);

        Clamp& set_type(clamp_type);

        Clamp& set_status(signal);

        Clamp& set_link_num(unsigned short);

        [[nodiscard]] const char* get_type() const noexcept;

        [[nodiscard]] const char* get_signal() const noexcept;

        [[nodiscard]] int get_link_num() const noexcept;

        void print(std::ostream&) const noexcept;

        Clamp& operator ++ ();

        Clamp& operator -- ();

        Clamp operator ++ (int);

        Clamp operator -- (int);

        void operator >> (Clamp& in_clamp);

        void operator << (Clamp& in_clamp);
    };
}

#endif //LAB2_CLAMP_H
