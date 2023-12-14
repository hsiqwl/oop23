cmake_minimum_required(VERSION 3.26)
project(necromant)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)
add_library(Necromant STATIC src/Necromant.cpp)

target_include_directories(Necromant PUBLIC include)
target_link_libraries(Necromant Creature Skill)
