cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)
add_library(Stairs STATIC src/Stairs.cpp)

target_include_directories(Stairs PUBLIC include)
target_link_libraries(Stairs Cell Interactable_cell Necromant)