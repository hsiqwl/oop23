#include "clamp/clamp.h"
#include <iostream>
namespace clamp_class {

     Clamp::Clamp(): type {in}, status {undefined}, link_num {0} {}

    Clamp::Clamp(clamp_type c_type, signal status, unsigned short link_nums) {
         if(c_type == in){
             if(link_nums>1 || link_nums<0)
                 throw clamp_exception("incorrect value of links num");
             else {
                 link_num = link_nums;
                 if(link_nums == 0)
                     this->status = undefined;
                 else
                     this->status = status;
             }
         }
         else if(c_type == clamp_type::out){
             if(link_nums<0 || link_nums>3)
                 throw clamp_exception("incorrect value of links num");
             else
                 link_num = link_nums;
         }
         else
             throw clamp_exception("incorrect value clamp type");
         type = c_type;
         this->status = status;
     }

    Clamp::Clamp(clamp_type c_type): Clamp(c_type, signal::undefined, 0){}

    Clamp& Clamp::set_type(clamp_type c_type){
         if(c_type < 0 || c_type>1)
             throw clamp_exception("incorrect value of clamp type");
         else
             type = c_type;
         return (*this);
     }

    Clamp& Clamp::set_status(signal signal_status) {
         if(signal_status < 0 || signal_status>2)
             throw clamp_exception("incorrect value of signal status");
         else
             status = signal_status;
         return (*this);
     }


    Clamp& Clamp::set_link_num(unsigned short num) {
         if(type == clamp_type::in){
             if(num>1 || num<0)
                 throw clamp_exception("incorrect value of links num");
             else
                 link_num = num;
         }else{
             if(num<0 || num>3)
                 throw clamp_exception("incorrect value of links num");
             else
                 link_num = num;
         }
         return (*this);
     }

     const char* Clamp::get_type() const noexcept{
         if(type == in)
             return "in";
         else
             return "out";
     }

    const char* Clamp::get_signal() const noexcept{
         if(status == high)
             return "high";
         if(status == low)
             return "low";
         else
             return "undefined";
     }

    int Clamp::get_link_num() const noexcept{
         return link_num;
     }

    void Clamp::print(std::ostream& s) const  noexcept{
        s<<"type:"<<this->get_type()<<" signal status:"<<this->get_signal()<<" link_num:"<<this->get_link_num()<<'\n';
     }

     Clamp& Clamp::operator++() { //prefix
         if(link_num<3){
             link_num++;
             return (*this);
         }else
             throw clamp_exception("trying to have too many links");
     }

     Clamp& Clamp::operator--() {
         if(link_num>0){
             link_num--;
             if(!link_num && type == in)
                 status = undefined;
             return (*this);
         }
         else
             throw clamp_exception("trying to have negative amount links");
     }

     Clamp Clamp::operator++(int) { //postfix
        Clamp copy = (*this);
         if(link_num<3){
             link_num++;
             return copy;
         }else
             throw clamp_exception("trying to have too many links");
     }

    Clamp Clamp::operator--(int) {
        Clamp copy = (*this);
        if(link_num>0){
            link_num--;
            if(!link_num && type == in)
                status = undefined;
            return copy;
        }else
            throw clamp_exception("trying to have negative amount of links");
    }

    void Clamp::operator >> (Clamp& obj){
         if(obj.type != type){
             if(obj.type == in)
                 obj.status = status;
             else
                 status = obj.status;
         }else
             throw clamp_exception("wrong operand clamp type");
    }

     void Clamp::operator<<(Clamp &obj) {
         if(obj.type!=type){
             if(obj.type == in)
                 obj.status = undefined;
             else
                 status = undefined;
         }else{
             throw clamp_exception("wrong operand clamp type");
         }
     }
}

