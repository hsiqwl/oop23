cmake_minimum_required(VERSION 3.26)
project(game_state)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g )
add_library(Game_state STATIC src/Game_state.cpp ../Matrix/include/matrix.h)

target_include_directories(Game_state PUBLIC include)
target_link_libraries(Game_state Necromant Cell)