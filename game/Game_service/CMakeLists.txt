cmake_minimum_required(VERSION 3.26)
project(game_service)
find_package(TBB REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -fsanitize=thread)
add_link_options(-fsanitize=thread)
add_library(Game_service STATIC src/Game_service.cpp)

target_include_directories(Game_service PUBLIC include)
target_link_libraries(Game_service Creature_service TBB::tbb Threads::Threads)
