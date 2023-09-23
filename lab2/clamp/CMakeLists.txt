cmake_minimum_required(VERSION 3.26)
project(clamp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)


add_library(Clamp STATIC src/clamp.cpp)

target_include_directories(Clamp PUBLIC include)