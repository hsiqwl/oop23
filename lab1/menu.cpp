#include "menu.h"
#include "matrix.h"
#include <iostream>
using namespace Matr;
namespace Menu{
    const char* options[] = {"1.input matrix", "2.output", "3.clear", "4.process", "5.close menu"};
    const int num_of_options = sizeof(options)/sizeof(options[0]);
    void show_menu(const char* options[], int num_of_options){
        for(int i = 0; i < num_of_options; i++){
            std::cout<<options[i]<<'\n';
        }
    }

    void run_command(int command, Matrix& matrix){
        switch(command){
            case 1:
                matrix = input();
                break;
            case 2:
                output(matrix);
                break;
            case 3:
                clear(matrix);
                break;
            case 4:
                process(matrix);
                break;
            case 5:
                std::cout<<"Closing now\n";
                break;
        }
    }

}