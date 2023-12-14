cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)

add_library(Door STATIC src/Door.cpp)

target_include_directories(Door PUBLIC include)
target_link_libraries(Door Cell Interactable_cell)