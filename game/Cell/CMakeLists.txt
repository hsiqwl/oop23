cmake_minimum_required(VERSION 3.26)
project(cell)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(base_cell)
add_subdirectory(interactable_cell)
add_subdirectory(Door)
add_subdirectory(Lava)
add_subdirectory(Stairs)
add_subdirectory(Essence)