cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)
add_library(Necromastery STATIC src/Necromastery.cpp)

target_include_directories(Necromastery PUBLIC include)
target_link_libraries(Necromastery Skill Undead)
