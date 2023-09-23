cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_library(lab1 utils.h matrix.h matrix.cpp InOut.h
        menu.h
        menu.cpp)

link_libraries(lab1)

add_executable(main main.cpp)
