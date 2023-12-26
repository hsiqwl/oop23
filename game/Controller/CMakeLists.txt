cmake_minimum_required(VERSION 3.26)
project(Controller)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)

add_library(Controller STATIC src/Controller.cpp)
target_include_directories(Controller PUBLIC include)
target_link_libraries(Controller sfml-graphics sfml-window sfml-system Game_service)
