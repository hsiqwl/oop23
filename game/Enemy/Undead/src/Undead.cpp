#include "../include/Undead.h"
#include <iostream>
Undead::Undead(std::string &name_, std::pair<size_t, size_t> coordinates_, size_t xp_after_death_,
               Undead::undead_type type_): Enemy(name_, Creature::Fraction::undead, coordinates_, xp_after_death_) {
    type = type_;
    Stats a = get_stats_by_type(type_);
    set_stats(get_stats_by_type(type_));
}


Stats Undead::get_stats_by_type(Undead::undead_type type_) {
    switch(type_)
    {
        case undead_type::skeleton:
        {
            return Stats(Undead::skeleton_stats);
        }
        case undead_type::zombie:
        {
            return Stats(Undead::zombie_stats);
        }
        case undead_type::ogre:
        {
            return Stats(Undead::ogre_stats);
        }
    }
}

/*!
 * @brief changes attributes such as stats and name according to a new Undead::undead_type given
 * @param new_type enum type parameter that will be set as a new value of a type attribute
 */

void Undead::change_attributes(Undead::undead_type new_type) {
    set_stats(get_stats_by_type(new_type));
    type = new_type;
    std::string new_name = get_name_by_type(new_type);
    set_name(new_name);

}
/*!
 * @brief static member function that sets stats for skeleton type objects
 */
void Undead::init_skeleton_stats() {
    Undead::skeleton_stats.set_incremential_rate(1.1);
    Undead::skeleton_stats.set_max_curr_xp(400);
    Undead::skeleton_stats.set_max_level(4);
    Undead::skeleton_stats.set_block_probability(0.05);
    Undead::skeleton_stats.set_curr_level(1);
    Undead::skeleton_stats.set_max_hp(30);
    Undead::skeleton_stats.set_curr_hp(30);
    Undead::skeleton_stats.set_base_dmg(10);
    Undead::skeleton_stats.set_max_mp(5);
    Undead::skeleton_stats.set_curr_mp(5);
}

/*!
 * @brief static member function that sets stats for ogre type objects
 */
void Undead::init_ogre_stats() {
    Undead::ogre_stats.set_incremential_rate(1.1);
    Undead::ogre_stats.set_max_curr_xp(400);
    Undead::ogre_stats.set_max_level(4);
    Undead::ogre_stats.set_block_probability(0.02);
    Undead::ogre_stats.set_curr_level(1);
    Undead::ogre_stats.set_max_hp(50);
    Undead::ogre_stats.set_curr_hp(50);
    Undead::ogre_stats.set_base_dmg(14);
    Undead::ogre_stats.set_max_mp(4);
    Undead::ogre_stats.set_curr_mp(4);
}

/*!
 * @brief static member function that sets stats for zombie type objects
 */
void Undead::init_zombie_stats() {
    Undead::zombie_stats.set_incremential_rate(1.1);
    Undead::zombie_stats.set_max_curr_xp(400);
    Undead::zombie_stats.set_max_level(4);
    Undead::zombie_stats.set_block_probability(0.13);
    Undead::zombie_stats.set_curr_level(1);
    Undead::zombie_stats.set_max_hp(34);
    Undead::zombie_stats.set_curr_hp(34);
    Undead::zombie_stats.set_base_dmg(15);
    Undead::zombie_stats.set_max_mp(3);
    Undead::zombie_stats.set_curr_mp(3);
}

/*!
 * @brief static member function that sets stats for different types of undead
 */
void Undead::init_stats() {
    Undead::init_skeleton_stats();
    Undead::init_ogre_stats();
    Undead::init_zombie_stats();
}
/*!
 * @brief chooses a name based on undead type
 * @param type_ enum type for undead type
 * @return string containing a name based on a type
 */

std::string Undead::get_name_by_type(Undead::undead_type type_) {
    switch(type_){
        case undead_type::skeleton:
            return static_cast<std::string>("skeleton");
        case undead_type::zombie:
            return static_cast<std::string>("zombie");
        case undead_type::ogre:
            return static_cast<std::string>("ogre");
    }
}