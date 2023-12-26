cmake_minimum_required(VERSION 3.26)
project(app)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)
add_executable(test src/test.cpp src/App.cpp ../Matrix/include/matrix.h)

target_include_directories(test PUBLIC include)
target_link_libraries(test config++ View Controller Stairs Undead Living Curse Dessication Morphism Necromastery sfml-window sfml-graphics)
