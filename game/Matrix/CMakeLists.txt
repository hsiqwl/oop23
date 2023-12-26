cmake_minimum_required(VERSION 3.26)
project(matrix)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(Matrix INTERFACE include/matrix.h)
add_library(dynamic_array INTERFACE include/dynamic_array.h)