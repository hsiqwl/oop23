#ifndef LAB1_INOUT_H
#define LAB1_INOUT_H
#include <iostream>
#include <limits>
#include <cstring>
#include <string>

namespace InOut{

    template <class Type>
    Type getNum(Type min = std::numeric_limits<Type>::min(),Type max = std::numeric_limits<Type>::max()){
        Type value;
        while(true){
            std::cin>>value;
            if(std::cin.eof())
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wrong input, repeat please!"<< std::endl;
            }
            else if(value >= min && value<= max)
                return value;
        }
    }

}


#endif //LAB1_INOUT_H
