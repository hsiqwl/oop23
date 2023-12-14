#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H
#include <vector>
#include <iostream>
template<std::default_initializable T>
class matrix{
private:
    std::vector<std::vector<T>> matr;
public:
    matrix() = default;
    matrix(size_t n): matrix(n, n){}
    matrix(size_t n, size_t m) {
        matr(n, std::vector<T>(m));
    }
    std::vector<T>& operator [] (size_t index) {
        return matr[index];
    }
    const std::vector<T> operator [] (size_t index) const{
        return matr[index];
    }

    void emplace_back_row(std::vector<T>& row){
        matr.emplace_back(row);
    }

    void add_column(std::vector<T>& column, int index){
        for(int i = 0; i < matr.size(); ++i)
            matr[i].insert(matr[i].begin() + index + 1, column[i]);
    }

    size_t get_columns() const{
        return matr[0].size();
    }

    size_t get_rows() const{
        return matr.size();
    }
};


#endif //LAB3_MATRIX_H
