#include <iostream>
#include "matrix.h"
#include "InOut.h"
#include "menu.h"
using namespace Matr;

int main() {
    Matrix matrix;
    try{
        int command;
        do{
            Menu::show_menu(Menu::options, Menu::num_of_options);
            command = InOut::getNum<int>(1,5);
            Menu::run_command(command,matrix);
        }while(command!=5);
    }
    catch(const std::bad_alloc& ba){
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
