cmake_minimum_required(VERSION 3.26)
project(creature_service)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)
add_library(Creature_service STATIC src/Creature_service.cpp)

target_include_directories(Creature_service PUBLIC include ../Enemy_service/include)
target_link_libraries(Creature_service Enemy_service Hero_service Golem Living Undead Lava Essence)
