#include "../include/Living.h"

Living::Living(std::string &name_, std::pair<size_t, size_t> coordinates_,
               size_t xp_after_death, Living::living_type type_): Enemy(name_, Creature::Fraction::living, coordinates_, xp_after_death) {
    type = type_;
    if(type == living_type::soldier)
        set_stats(Living::soldier_stats);
    else
        set_stats(Living::knight_stats);
}
/*!
 * @brief static member function that sets stats for Living_type::soldier objects
 */
void Living::init_soldier_stats() {
    Living::soldier_stats.set_incremential_rate(1.2);
    Living::soldier_stats.set_max_curr_xp(400);
    Living::soldier_stats.set_max_level(4);
    Living::soldier_stats.set_block_probability(0.12);
    Living::soldier_stats.set_curr_level(1);
    Living::soldier_stats.set_max_hp(30);
    Living::soldier_stats.set_curr_hp(30);
    Living::soldier_stats.set_base_dmg(10);
    Living::soldier_stats.set_max_mp(10);
    Living::soldier_stats.set_curr_mp(10);
}

/*!
 * @brief static member function that sets stats for Living_type::knight objects
 */
void Living::init_knight_stats() {
    Living::knight_stats.set_incremential_rate(1.1);
    Living::knight_stats.set_max_curr_xp(400);
    Living::knight_stats.set_max_level(4);
    Living::knight_stats.set_block_probability(0.13);
    Living::knight_stats.set_curr_level(1);
    Living::knight_stats.set_max_hp(40);
    Living::knight_stats.set_curr_hp(40);
    Living::knight_stats.set_base_dmg(12);
    Living::knight_stats.set_max_mp(5);
    Living::knight_stats.set_curr_mp(5);
}

void Living::init_stats() {
    Living::init_knight_stats();
    Living::init_soldier_stats();
}