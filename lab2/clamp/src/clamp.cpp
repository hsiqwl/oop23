#include "clamp/clamp.h"
#include <iostream>
#include <format>
namespace clamp_class {

    Clamp::Clamp(): type{in}, status{undefined}, link_num{0} {}

    Clamp::Clamp(clamp_type c_type = in, signal status = undefined, unsigned short link_nums = 0) {
        if (c_type == in && (link_nums > 1 || link_nums < 0))
                throw std::invalid_argument("incorrect value of links num");
        else if (c_type == out && (link_nums < 0 || link_nums > 3))
            throw std::invalid_argument("incorrect value of links num");
        else
            throw std::invalid_argument("incorrect value of clamp type");

        if(link_nums == 0)
            this->status = undefined;
        else
            this->status = status;
        type = c_type;
        this->link_num = link_nums;
    }

    Clamp::Clamp(clamp_type c_type) : Clamp(c_type, signal::undefined, 0) {}

    Clamp &Clamp::set_type(clamp_type c_type) {
        if (c_type < 0 || c_type > 1)
            throw std::invalid_argument("incorrect value of clamp type");
        else
            type = c_type;
        return (*this);
    }

    Clamp &Clamp::set_status(signal signal_status) {
        if (signal_status < 0 || signal_status > 2)
            throw std::invalid_argument("incorrect value of signal status");
        else {
            if (link_num != 0)
                status = signal_status;
            else
                throw std::invalid_argument("can't have non undefined signal on this clamp");
        }
        return (*this);
    }


    Clamp &Clamp::set_link_num(unsigned short num) {
        if (type == clamp_type::in) {
            if (num > 1 || num < 0)
                throw std::invalid_argument("incorrect value of link_num");
            else
                link_num = num;
        } else {
            if (num < 0 || num > 3)
                throw std::invalid_argument("incorrect value of link_num");
            else
                link_num = num;
        }
        return (*this);
    }

    clamp_type Clamp::get_type() const noexcept {
        return type;
    }

    signal Clamp::get_signal() const noexcept {
        return status;
    }

    int Clamp::get_link_num() const noexcept {
        return link_num;
    }

    void Clamp::print(std::ostream &s) const noexcept{
        std::string _type = type == in ? "in" : "out";
        std::string _status;
        if(status == high)
            _status = "high";
        else if(status == low)
            _status = "low";
        else
            _status = "undefined";
        std::string formatted = std::format("type:{}, signal status:{}, link_num:{}\n", _type, _status, link_num);
        s << formatted;
    }

    Clamp &Clamp::operator++() { //prefix
        if (type == in && link_num > 0)
            throw std::logic_error("trying to have too many links");
        if (type == out && link_num > 2)
            throw std::logic_error("trying to have too many links");
        ++link_num;
        return (*this);
    }

    Clamp &Clamp::operator--() {
        if (link_num > 0) {
            link_num--;
            if (!link_num)
                status = undefined;
            return (*this);
        } else
            throw std::logic_error("trying to have negative amount links");
    }

    Clamp Clamp::operator++(int) { //postfix
        Clamp copy = (*this);
        if (type == in && link_num > 0)
            throw std::logic_error("trying to have too many links");
        if (type == out && link_num > 2)
            throw std::logic_error("trying to have too many links");
        ++link_num;
        return copy;
    }

    Clamp Clamp::operator--(int) {
        Clamp copy = (*this);
        if (link_num > 0) {
            link_num--;
            if (!link_num)
                status = undefined;
            return copy;
        } else
            throw std::logic_error("trying to have negative amount of links");
    }

    void Clamp::operator>>(Clamp &obj) {
        if (obj.type != type) {
            if (obj.type == in)
                obj.status = status;
            else
                status = obj.status;
        } else
            throw std::invalid_argument("wrong operand clamp type");
    }

    void Clamp::operator<<(Clamp &obj) {
        if (obj.type != type) {
            if (obj.type == in)
                obj.status = undefined;
            else
                status = undefined;
        } else {
            throw std::invalid_argument("wrong operand clamp type");
        }
    }

    void Clamp::operator!() {
        if (status != undefined)
            status = static_cast<signal>(!(static_cast<int>(status)));
        else
            throw std::logic_error("can't reverse undefined signal");
    }

    std::ostream& operator << (std::ostream& s, const Clamp& obj){
        obj.print(s);
        return s;
    }
}


