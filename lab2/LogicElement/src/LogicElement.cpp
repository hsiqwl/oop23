#include "LogicElement/LogicElement.h"
#include "clamp/clamp.h"
#include <iostream>
#include <utility>
#include <compare>
using namespace clamp_class;
namespace LogicElementClass{

    void LogicElement::resize_arr(size_t new_len){
        Clamp* new_arr = new Clamp[new_len];
        std::copy(arr, arr + curr_size, new_arr);
        delete[] arr;
        arr = new_arr;
        max_size = new_len;
    }

    /*!
     @param num_of_in number of clamps with type in
     @param num_of_out number of clamps with type out
     @throws std::bad_alloc in case of a problem with allocating memory
    */
    LogicElement::LogicElement(size_t num_of_out, size_t num_of_in) {
        arr = new Clamp[num_of_in + num_of_out];
        max_size = curr_size = num_of_out + num_of_in;
        for (int i = 0; i < num_of_out; ++i) {
            arr[i] = Clamp(out);
        }
        for (unsigned int i = num_of_out; i < curr_size; ++i) {
            arr[i] = Clamp(in);
        }
    }

    /*!
     @param array pointer to Clamp type, array of clamps
     @param arr_len length of an array
     @throws std::bad_alloc in case of a problem with allocating memory
    */
    LogicElement::LogicElement(Clamp* array, size_t arr_len) {
        arr = new Clamp[arr_len];
        max_size = curr_size = arr_len;
        std::copy(array, array + arr_len, arr);
    }

    /*!
        @returns number of clamps with type "in"
    */
    size_t LogicElement::get_num_of_in() const {
        size_t num_of_in = 0;
        for(size_t i = 0; i < curr_size;++i){
            if(arr[i].get_type() == in)
                num_of_in++;
        }
        return num_of_in;
    }

    /*!
        @returns number of clamps with type "out"
    */
    size_t LogicElement::get_num_of_out() const {
        size_t num_of_out = 0;
        for(size_t i = 0; i < curr_size;++i){
            if(arr[i].get_type() == out)
                num_of_out++;
        }
        return num_of_out;
    }

    /*!
     @param obj const reference to an LogicElement type object that will be copied
     @throws std::bad_alloc in case of troubles with allocating memory
    */
    LogicElement::LogicElement(const LogicElement &obj){
        arr = nullptr;
        if(obj.max_size != 0){
            arr = new Clamp[max_size];
            std::copy(obj.arr, obj.arr + obj.curr_size, arr);
            curr_size = obj.curr_size;
            max_size = obj.max_size;
        }
    }

    /*!
     @param obj const reference to an LogicElement type object that will be copied
     @throws std::bad_alloc in case of troubles with allocating memory
     @returns reference to an object of LogicElement type
    */
    LogicElement& LogicElement::operator = (const LogicElement& obj){
        if(this == &obj)
            return *this;
        Clamp* new_arr = new Clamp[obj.max_size];
        delete[] arr;
        std::copy(obj.arr, obj.arr+ obj.curr_size, new_arr);
        curr_size = obj.curr_size;
        max_size = obj.max_size;
        arr = new_arr;
        return *this;
    }

    /*!
     @param obj an && reference to an LogicElement type object which data will be moved
    */
    LogicElement::LogicElement(LogicElementClass::LogicElement &&obj) noexcept {
        max_size = std::exchange(obj.max_size,0);
        curr_size = std::exchange(obj.curr_size,0);
        arr = std::exchange(obj.arr, nullptr);
    }

    /*!
     @param obj an && reference to an LogicElement type object which data will be moved
     @returns a reference to LogicElement object
    */
    LogicElement& LogicElement::operator=(LogicElement &&obj) noexcept{
        delete[] arr;
        max_size = std::exchange(obj.max_size,0);
        curr_size = std::exchange(obj.curr_size,0);
        arr = std::exchange(obj.arr, nullptr);
        return *this;
    }

    /*!
     @param array array of signals to resetting
     @param arr_len length of array
     @throws std::invalid_argument in case of passing an array length that doesnt match to the curr_size of an object
     @returns reference to LogicElement object
    */
    LogicElement& LogicElement::reset_signals(signal* array, size_t arr_len){
        if(arr_len!=curr_size)
            throw std::invalid_argument("passing incorrect array length");
        else{
            for (int i = 0; i < arr_len; ++i) {
                try {
                    arr[i].set_status(array[i]);
                }
                catch (std::exception &e) {
                    std::cerr << e.what() <<'\n';
                }
            }
            return (*this);
        }
    }

    /*!
     @param obj reference to Clamp type object to be added
     @returns reference to LogicElement object with new clamp
    */
    LogicElement& LogicElement::add_clamp(Clamp& obj) {
        if(curr_size == max_size)
            resize_arr(max_size + resize_var);
        arr[curr_size++] = obj;
        return (*this);
    }

    /*!
     @param obj reference to LogicElement type object to connect with
     @throws std::logic_error in case of not being able to connect elements
    */
    void LogicElement::operator >> (LogicElement& obj) const{
        unsigned pos_out = -1, pos_in = -1;
        for(int i = 0; i < curr_size; ++i){
            if(arr[i].get_link_num() < 3 && arr[i].get_type() == out){
                pos_out = i;
                break;
            }
        }
        for(int i = 0; i < obj.curr_size; ++i){
            if(obj.arr[i].get_link_num() < 1 && obj.arr[i].get_type()==in){
                pos_in = i;
                break;
            }
        }
        if(pos_in!=-1 && pos_out!=-1)
            (++arr[pos_out]) >> (++obj.arr[pos_in]);
        else
            throw std::logic_error("can't link elements");
    }

    /*!
     @param index an index of an object in array to be returned
     @throws std::out_of_range in case of index being out of range of an array length
     @returns reference to Clamp type object
    */
    Clamp& LogicElement::operator[](size_t index) {
        if(index >= curr_size)
            throw std::out_of_range("index is out of range");
        else
            return arr[index];
    }

    const Clamp& LogicElement::operator[](size_t index) const{
        if(index >= curr_size)
            throw std::out_of_range("index is out of range");
        else
            return arr[index];
    }

    /*!
     @param obj reference to LogicElement type object to be compared with
     @returns a std::weak_ordering type object
    */
    std::weak_ordering LogicElement::operator <=>(const LogicElement& obj) const{
        size_t a = this->get_num_of_in();
        size_t b = obj.get_num_of_in();
        if(a > b)
            return std::weak_ordering::greater;
        else if (a < b)
            return std::weak_ordering::less;
        else
            return std::weak_ordering::equivalent;
    }

    std::ostream& operator << (std::ostream& s,const LogicElement& obj){
        s << "curr_size:" << obj.curr_size << "max_size:" << obj.max_size << '\n';
        for(int i = 0; i < obj.curr_size; ++i){
            obj.arr[i].print(s);
            s << '\n';
        }
        return s;
    }

    std::istream& operator >> (std::istream& s, LogicElement& obj){
        size_t num_of_in;
        size_t num_of_out;
        s >> num_of_in >> num_of_out;
        if(s.good()){
            if(num_of_in < 0 || num_of_out < 0){
                s.setstate(std::ios::failbit);
            }else {
                delete[] obj.arr;
                obj.max_size = obj.curr_size = num_of_out + num_of_in;
                obj.arr = new Clamp[obj.max_size];
                for(size_t i = 0; i < num_of_in; ++i){
                    obj.arr[i] = Clamp(in);
                }
                for(size_t i = num_of_in; i < obj.max_size; ++i){
                    obj.arr[i] = Clamp(out);
                }
            }
        }
        return s;
    }
}