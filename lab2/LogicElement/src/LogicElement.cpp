#include "LogicElement/LogicElement.h"
#include "clamp/clamp.h"
#include <iostream>
#include <utility>
using namespace clamp_class;
namespace LogicElementClass{

    void LogicElement::resize_arr(size_t new_len){
        Clamp* new_arr = new Clamp[new_len];
        std::copy(arr, arr + curr_size, new_arr);
        delete[] arr;
        arr = new_arr;
        max_size = new_len;
    }

    LogicElement::LogicElement(size_t num_of_out, size_t num_of_in) {
        arr = new Clamp[num_of_in + num_of_out];
        max_size = curr_size = num_of_out + num_of_in;
        for (int i = 0; i < num_of_in; ++i) {
            arr[i] = Clamp(in);
        }
        for (unsigned int i = num_of_in; i < curr_size; ++i) {
            arr[i] = Clamp(out);
        }
    }

    LogicElement::LogicElement(Clamp* array, size_t arr_len) {
        arr = new Clamp[arr_len];
        max_size = curr_size = arr_len;
        std::copy(array, array + arr_len, arr);
    }

    LogicElement::LogicElement(const LogicElement &obj){
        arr = nullptr;
        if(obj.max_size != 0){
            arr = new Clamp[max_size];
            std::copy(obj.arr, obj.arr + obj.curr_size, arr);
            curr_size = obj.curr_size;
            max_size = obj.max_size;
        }
    }

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

    LogicElement::LogicElement(LogicElementClass::LogicElement &&obj) noexcept {
        max_size = obj.max_size;
        curr_size = obj.curr_size;
        arr = obj.arr;
        obj.arr = nullptr;
    }

    LogicElement& LogicElement::operator=(LogicElement &&obj) noexcept{
        delete[] arr;
        max_size = std::exchange(obj.max_size,0);
        curr_size = std::exchange(obj.curr_size,0);
        arr = std::exchange(obj.arr, nullptr);
        return *this;
    }

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

    LogicElement& LogicElement::add_clamp(Clamp& obj) {
        if(curr_size == max_size)
            resize_arr(max_size + resize_var);
        arr[curr_size++] = obj;
        return (*this);
    }

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

    Clamp& LogicElement::operator[](size_t index) const {
        if(index >= curr_size)
            throw std::out_of_range("index is out of range");
        else
            return arr[index];
    }
}