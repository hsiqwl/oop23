#include "clamp/clamp.h"
#include <iostream>
#include <format>
namespace clamp_class {

    Clamp::Clamp(): type{in}, status{undefined}, link_num{0} {}

    /*!
    @param c_type type of a clamp, by default is "in" type
    @param status type of a signal, by default is "undefined"
     @param link_nums the number of other clamps that this objects is connected to
     @throws std::invalid_argument in case of incorrect clamp type or incorrect number of links for specific type
    */
    Clamp::Clamp(clamp_type c_type = in, signal status = undefined, unsigned short link_nums = 0) {
        if (c_type != in && c_type != out)
            throw std::invalid_argument("incorrect value of clamp type");
        if (c_type == in && (link_nums > 1 || link_nums < 0))
                throw std::invalid_argument("incorrect value of links num");
        else if (c_type == out && (link_nums < 0 || link_nums > 3))
            throw std::invalid_argument("incorrect value of links num");
        if(link_nums == 0)
            this->status = undefined;
        else
            this->status = status;
        type = c_type;
        this->link_num = link_nums;
    }

    /*!
    @param c_type type of a clamp
     @throws std::invalid_argument in case of incorrect clamp type
    */
    Clamp::Clamp(clamp_type c_type) : Clamp(c_type, signal::undefined, 0) {}

    /*!
    @param c_type type of a clamp
     @throws std::invalid_argument in case of incorrect clamp type
     @throws std::logic_error in case the clamp is linked to other one
     @returns a reference to an object with new-set type
    */
    Clamp &Clamp::set_type(clamp_type c_type) {
        if (c_type != in && c_type != out)
            throw std::invalid_argument("incorrect value of clamp type");
        else if(link_num == 0)
            type = c_type;
        else
            throw std::logic_error("can't change type because it's linked");
        return (*this);
    }
    /*!
    @param signal_status type of a signal
     @throws std::invalid_argument in case of incorrect type of a signal
     @returns reference to an object with new-set signal
    */
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

    /*!
    @param num number of objects connected to this
     @throws std::invalid_argument in case of incorrect value of num
     @returns reference to an object with new-set link number
    */
    Clamp &Clamp::set_link_num(unsigned short num) {
        if (type == in) {
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

    /*!
     @returns type of a clamp
    */
    clamp_type Clamp::get_type() const noexcept {
        return type;
    }
    /*!
     @returns type of a clamp signal
    */
    signal Clamp::get_signal() const noexcept {
        return status;
    }
    /*!
     @returns the number of links of a clamp
    */
    int Clamp::get_link_num() const noexcept {
        return link_num;
    }

    /*!
     @param s reference to an std::ostream object
    */
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

    /*!
     @throws std::logic_error in case of increasing the number of links too much for a specific clamp type
     @returns reference to an object after the change
    */
    Clamp &Clamp::operator++() { //prefix
        if (type == in && link_num > 0)
            throw std::logic_error("trying to have too many links");
        if (type == out && link_num > 2)
            throw std::logic_error("trying to have too many links");
        ++link_num;
        return (*this);
    }
    /*!
     @throws std::logic_error in case of decreasing the number of links to a negative number
     @returns reference to an object after the change
    */
    Clamp &Clamp::operator--() {
        if (link_num > 0) {
            link_num--;
            if (!link_num)
                status = undefined;
            return (*this);
        } else
            throw std::logic_error("trying to have negative amount links");
    }

    /*!
     @throws std::logic_error in case of increasing the number of links too much for a specific clamp type
     @returns an object before the change
    */
    Clamp Clamp::operator++(int) { //postfix
        Clamp copy = (*this);
        if (type == in && link_num > 0)
            throw std::logic_error("trying to have too many links");
        if (type == out && link_num > 2)
            throw std::logic_error("trying to have too many links");
        ++link_num;
        return copy;
    }

    /*!
     @throws std::logic_error in case of decreasing the number of links to a negative number
     @returns an object before the change
    */
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

    /*!
     @param obj reference to an clamp class object
     @throws std::invalid_argument in case of passing an object with the same type
    */
    void Clamp::operator>>(Clamp &obj) {
        if (obj.type != type) {
            if (obj.type == in)
                obj.status = status;
            else
                status = obj.status;
        } else
            throw std::invalid_argument("wrong operand clamp type");
    }

    /*!
     @param obj reference to an clamp class object
     @throws std::invalid_argument in case of passing an object with the same type
    */
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

    /*!
       @throws std::logic_error in case of reversing an undefined signal
    */
    void Clamp::operator!() {
        if (status != undefined)
            status = static_cast<signal>(!(static_cast<int>(status)));
        else
            throw std::logic_error("can't reverse undefined signal");
    }

    /*!
     @param s reference to an std::ostream type object
     @param obj reference to an clamp class object
     @returns reference to an std::ostream type object
    */
    std::ostream& operator << (std::ostream& s, const Clamp& obj){
        obj.print(s);
        return s;
    }
}


