#ifndef DIALOGUE_LOGICELEMENT_H
#define DIALOGUE_LOGICELEMENT_H
#include <clamp/clamp.h>

using namespace clamp_class;

namespace LogicElementClass{
    class LogicElement{
    private:
        static const int logic_element_arr_max_size = 50;
        int curr_size;
        Clamp arr[logic_element_arr_max_size];
    };

}


#endif //DIALOGUE_LOGICELEMENT_H
