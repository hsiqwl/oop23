cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(Dessication STATIC src/Dessication.cpp)

target_include_directories(Dessication PUBLIC include)
target_link_libraries(Dessication Skill Necromant config++)
