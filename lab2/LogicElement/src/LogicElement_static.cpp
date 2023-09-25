#include "LogicElement/LogicElement_static.h"
#include "clamp/clamp.h"

using namespace clamp_class;
namespace LogicElementClass{

    LogicElement::LogicElement(unsigned num_of_out, unsigned num_of_in){
        if(num_of_in + num_of_out < logic_element_arr_max_size){
            curr_size = num_of_out + num_of_in;
            for(int i = 0; i < num_of_in;++i){
                arr[i] = Clamp(in);
            }
            for(unsigned int i = num_of_in; i < num_of_out;++i){
                arr[i] = Clamp(out);
            }
        }else
            throw LogicElementException("too many elements");
    }

    LogicElement::LogicElement(Clamp array[], unsigned  int arr_len) {
        if(arr_len < logic_element_arr_max_size){
            for(int i = 0; i < arr_len;++i)
                arr[i] = array[i];
            curr_size = arr_len;
        }else
            throw LogicElementException("too many elements");
    }

    LogicElement& LogicElement::reset_signals(signal array[], unsigned int arr_len){
        if(arr_len!=curr_size)
            throw LogicElementException("passing incorrect array length");
        else{
            for (int i = 0; i < arr_len; ++i) {
                try {
                    arr[i].set_status(array[i]);
                }
                catch (clamp_exception &e) {
                    std::cout << e.exception_info()<<'\n';
                }
            }
        }
    }

    LogicElement& LogicElement::add_clamp(Clamp& obj) {
        if(++curr_size < logic_element_arr_max_size)
            arr[curr_size] = obj;
        else{
            --curr_size;
            throw LogicElementException("no more space on LogicElement");
        }
    }

    void LogicElement::operator >> (LogicElement& obj){
        unsigned pos_out = -1, pos_in = -1;
        for(int i = 0; i < curr_size; ++i){
            if(arr[i].get_link_num < 3 && strcmp(arr[i].get_type(), "out")==0){
                pos_out = i;
                break;
            }
        }
        for(int i = 0; i < obj.curr_size; ++i){
            if(obj.arr[i].get_link_num < 1 && strcmp(obj.arr[i].get_type(), "in")==0){
                pos_in = i;
                break;
            }
        }
        (++arr[pos_out]) >> (++obj.arr[pos_in]);
    }

    Clamp& LogicElement::operator[](unsigned int index) {
        if(index > curr_size)
            throw LogicElementException("index is out of range");
        else
            return arr[index];
    }
}