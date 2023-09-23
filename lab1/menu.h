#ifndef LAB1_MENU_H
#define LAB1_MENU_H
#include "matrix.h"
using Matr::Matrix;
namespace Menu{
    extern const char* options[];
    extern const int num_of_options;
    void show_menu(const char* options[], int num_of_options);
    void run_command(int command, Matrix& matrix);
}

#endif //LAB1_MENU_H
