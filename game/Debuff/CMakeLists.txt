cmake_minimum_required(VERSION 3.26)
project(debuff)

set(CMAKE_CXX_STANDARD 20)

add_library(Debuff STATIC src/lava_debuff.cpp)

target_include_directories(Debuff PUBLIC include ../Creature/include)
