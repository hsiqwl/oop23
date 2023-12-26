cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(Curse STATIC src/Curse.cpp)

target_include_directories(Curse PUBLIC include)
target_link_libraries(Curse Skill)
