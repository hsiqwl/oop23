cmake_minimum_required(VERSION 3.26)
project(hero_service)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage)
add_link_options(--coverage)
add_library(Hero_service STATIC src/Hero_service.cpp)

target_include_directories(Hero_service PUBLIC include)
target_link_libraries(Hero_service Game_state Interactable_cell)
