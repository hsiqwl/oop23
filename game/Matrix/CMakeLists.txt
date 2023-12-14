cmake_minimum_required(VERSION 3.26)
project(matrix)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)
add_library(Matrix INTERFACE include/matrix.h)