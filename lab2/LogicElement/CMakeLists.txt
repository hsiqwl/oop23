cmake_minimum_required(VERSION 3.26)
project(LogicElement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
add_compile_options(-lgcov --coverage)
add_link_options(--coverage)
add_library(LogicElement STATIC src/LogicElement.cpp)

target_include_directories(LogicElement PUBLIC include)
target_link_libraries(LogicElement Clamp LibUtils)