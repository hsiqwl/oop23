#ifndef LAB1_UTILS_H
#define LAB1_UTILS_H

#include <algorithm>

namespace utils {
    template<class Type>
    void swap_values(Type &A, Type &B) {
        Type temp = A;
        A = B;
        B = temp;
    }

    template<class Type>
    Type is_less(const Type a, const Type b) {
        return a < b;
    }

    template<class Type>
    Type is_greater(const Type a, const Type b) {
        return a > b;
    }

    /*template <class T>
    void my_realloc(T** arr, int old_count, int new_count){
        T* tmp = new T[new_count];
        for(int i = 0; i < old_count;i++){
            tmp[i] = (*arr)[i];
        }
        delete[] (*arr);
        (*arr) = tmp;
    }
     */
}

#endif //LAB1_UTILS_H
