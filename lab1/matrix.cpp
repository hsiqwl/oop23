#include "matrix.h"
#include "InOut.h"
#include "utils.h"
using namespace InOut;
using namespace utils;
using std::cout;
namespace Matr{
    Matrix input(){
        Matrix matrix{};
        try {
            cout << "Enter number of rows-->";
            matrix.m = getNum(0);
            cout << "Enter number of columns-->";
            matrix.n = getNum(0);
            matrix.num_of_non_zero.push_back(0);
            for (int i = 0; i < matrix.m; i++) {
                int count = 0;
                cout << "Enter elements in row #" << (i + 1) << "-->";
                for (int j = 0; j < matrix.n; j++) {
                    double value = getNum<double>(-1000,1000);
                    if (value != 0) {
                        count++;
                        matrix.data.push_back(value);
                        matrix.column_index.push_back(j);
                    }else
                        continue;
                }
                matrix.num_of_non_zero.push_back(matrix.num_of_non_zero[i] + count);
            }
            matrix.data.shrink_to_fit();
            matrix.column_index.shrink_to_fit();
            matrix.num_of_non_zero.shrink_to_fit();
        }
        catch (...){
            throw;
        }
        return matrix;
    }

    int find_index(const vector<int>& column_index, int from, int to, int value){
        for(int i = from; i < to; i++){
            if(column_index[i] == value){
                return i;
            }
        }
        return -1;
    }

    void define_val_by_index(const Matrix& matrix, double& val, int col_ind, int row_ind){
        int pos = find_index(matrix.column_index,matrix.num_of_non_zero[row_ind-1],matrix.num_of_non_zero[row_ind],col_ind);
        if(pos!=-1)
            val = matrix.data[pos];
        else
            val = 0;
    }

    bool find_first_greater(Matrix& matrix, int& first_ind, int row_ind){
        for(int j = 0; j < matrix.n - 1;j++){
            double val1, val2;
            define_val_by_index(matrix,val1,j,row_ind);
            define_val_by_index(matrix,val2,j+1,row_ind);
            //cout<<"val1:"<<val1<<" "<<"val2:"<<val2<<'\n';
            if(val1 < val2){
                first_ind = j+1;
                return true;
            }
        }
        return false;
    }

    bool find_last_less(Matrix& matrix, int& second_ind, int row_ind){
        for(int j = matrix.n - 1; j > 0;j--){
            double val1, val2;
            define_val_by_index(matrix,val1,j,row_ind);
            define_val_by_index(matrix,val2,j-1,row_ind);
            //cout<<"val1:"<<val1<<" "<<"val2:"<<val2<<'\n';
            if(val1 < val2){
                second_ind = j;
                return true;
            }
        }
        return false;
    }

    void process(Matrix& matrix){
        for(int i = 1; i < matrix.m + 1;i++){
            int first_ind, second_ind;
            bool first_greater = find_first_greater(matrix, first_ind, i);
            bool last_less = find_last_less(matrix, second_ind, i);
            if(first_greater && last_less){
                int pos1 = find_index(matrix.column_index, matrix.num_of_non_zero[i-1], matrix.num_of_non_zero[i], first_ind);
                int pos2 = find_index(matrix.column_index, matrix.num_of_non_zero[i-1], matrix.num_of_non_zero[i], second_ind);
                //cout<<"pos1-"<<pos1<<" "<<"pos2-"<<pos2<<'\n';
                if(pos1!=-1 && pos2!=-1){
                    //cout<<"case1\n";
                    swap_values<double>(matrix.data[pos1],matrix.data[pos2]);
                }else if(pos2 != -1){
                    //cout<<"case2\n";
                    while(matrix.column_index[pos2-1] > first_ind && pos2>0 && pos2-1 > matrix.num_of_non_zero[i-1]) {
                        swap_values(matrix.data[pos2], matrix.data[pos2 - 1]);
                        swap_values(matrix.column_index[pos2], matrix.column_index[pos2-1]);
                        pos2--;
                    }
                    matrix.column_index[pos2] = first_ind;
                }else if(pos1 != -1){
                    //cout<<"case3\n";
                    while((pos1 < matrix.num_of_non_zero[matrix.m] - 1) && matrix.column_index[pos1+1] < second_ind && pos1+1 < matrix.num_of_non_zero[i]){
                        swap_values(matrix.data[pos1], matrix.data[pos1+1]);
                        swap_values(matrix.column_index[pos1], matrix.column_index[pos1+1]);
                        pos1++;
                    }
                    matrix.column_index[pos1] = second_ind;
                }
            }
        }
    }

    void output(const Matrix& matrix){
        cout<<"outputing matrix\n";
        for(int i = 1; i < matrix.m + 1;i++){
            for(int j = 0; j < matrix.n; j++){
                int pos = find_index(matrix.column_index, matrix.num_of_non_zero[i-1], matrix.num_of_non_zero[i],j);
                if(pos!=-1)
                    cout<<matrix.data[pos]<<" ";
                else
                    cout<<0<<" ";
            }
            cout<<'\n';
        }
    }

    void clear(Matrix& matrix){
        matrix.column_index.clear();
        matrix.num_of_non_zero.clear();
        matrix.data.clear();
        matrix.n = 0;
        matrix.m = 0;
    }

}