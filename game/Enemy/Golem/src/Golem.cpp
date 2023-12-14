#include "../include/Golem.h"
#include <stdexcept>
#include <iostream>
Golem::Golem(std::string &name_, std::pair<size_t, size_t> coordinates_,
             size_t xp_after_death_, Golem::golem_type type_): Enemy(name_, Creature::Fraction::golem, coordinates_, xp_after_death_){
    type = type_;
    set_stats(golem_stats);
}

/*!
 * @brief static member function that sets base stats for different types of golems
 */
void Golem::init_golem_stats() {
    Golem::golem_stats.set_max_level(4);
    Golem::golem_stats.set_curr_level(1);
    Golem::golem_stats.set_max_mp(3);
    Golem::golem_stats.set_curr_mp(3);
    Golem::golem_stats.set_max_hp(40);
    Golem::golem_stats.set_base_dmg(15);
    Golem::golem_stats.set_block_probability(0.15);
    Golem::golem_stats.set_max_curr_xp(400);
    Golem::golem_stats.set_incremential_rate(1.2);
    Golem::golem_stats.set_curr_hp(40);
}