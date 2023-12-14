cmake_minimum_required(VERSION 3.26)
project(creature)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g --coverage -fsanitize=thread)
add_link_options(--coverage -fsanitize=thread)

add_library(Creature STATIC src/Creature.cpp )

target_include_directories(Creature PUBLIC include )
target_link_libraries(Creature Stats)
