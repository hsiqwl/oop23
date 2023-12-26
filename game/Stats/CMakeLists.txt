cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(Stats STATIC src/Stats.cpp)

target_include_directories(Stats PUBLIC include)
