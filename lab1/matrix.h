#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <limits>
#include <cstring>
#include <string>
#include <vector>
using std::vector;

namespace Matr{
    struct Matrix{ //using compressed sparse row(CSR) to contain sparse matrix
        vector<double> data;
        vector<int> column_index;
        vector<int> num_of_non_zero;
        int m; // number of rows
        int n; // number of columns
    };
    Matrix input();
    void output(const Matrix& matr);
    int find_index(const vector<int>& column_index, int from, int to, int value);
    void process(Matrix& matrix);
    void define_val_by_index(const Matrix& matrix, double& val, int col_ind, int row_ind);
    bool find_first_greater(Matrix& matrix, int& first_ind, int row_ind);
    bool find_last_less(Matrix& matrix, int& second_ind, int row_ind);
    void clear(Matrix& matrix);
}

#endif