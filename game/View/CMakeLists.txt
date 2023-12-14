cmake_minimum_required(VERSION 3.26)
project(view)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)
add_library(View src/View.cpp ../Matrix/include/matrix.h)

target_include_directories(View PUBLIC include)
target_link_libraries(View sfml-graphics Cell Game_state Undead Living)