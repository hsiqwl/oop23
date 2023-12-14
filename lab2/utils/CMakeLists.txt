cmake_minimum_required(VERSION 3.26)
project(LibUtils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)


add_library(LibUtils INTERFACE)

target_include_directories(LibUtils INTERFACE include)