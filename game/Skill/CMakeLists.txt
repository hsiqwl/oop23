cmake_minimum_required(VERSION 3.26)
project(skill)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)
add_library(Skill STATIC Skill_interface/src/Skill_interface.cpp)

target_link_libraries(Skill Creature)

add_subdirectory(Morphism)
add_subdirectory(Dessication)
add_subdirectory(Curse)
add_subdirectory(Necromastery)