cmake_minimum_required(VERSION 3.26)
project(Dialogue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

add_library(Dialog STATIC src/dialogue.cpp)
target_include_directories(Dialog PUBLIC include)
target_link_libraries(Dialog Clamp LibUtils)
add_executable(main src/main.cpp)


target_link_libraries(main Dialog Clamp LibUtils)