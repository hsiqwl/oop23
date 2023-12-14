cmake_minimum_required(VERSION 3.26)
project(stats)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)

add_library(Interactable_cell INTERFACE)

target_include_directories(Interactable_cell INTERFACE include)
target_link_libraries(Interactable_cell INTERFACE Necromant)
