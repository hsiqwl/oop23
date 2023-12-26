cmake_minimum_required(VERSION 3.26)
project(enemy_service)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)

add_library(Enemy_service STATIC src/Enemy_service.cpp)

target_include_directories(Enemy_service PUBLIC include)
target_link_libraries(Enemy_service Game_state Enemy)
