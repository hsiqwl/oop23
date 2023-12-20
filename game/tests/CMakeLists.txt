find_package(Catch2 2 REQUIRED)
add_compile_options(--coverage)
add_link_options(--coverage)
add_executable(tests tests.cpp)
target_link_libraries(tests Stats Creature Enemy Undead Necromant Skill Curse Dessication Morphism
        dynamic_array Game_state Cell Living Catch2::Catch2)