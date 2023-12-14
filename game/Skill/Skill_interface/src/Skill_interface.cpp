#include "../include/Skill.h"

/*!
 * @brief setter for a skill name
 * @param name_ string that contains a name
 */
void Skill::set_name(const std::string &name_) {
    name = name_;
}
/*!
 * @brief sets a development level of a skill, can't be greater than max_development
 * @param development_ value to be set
 */
void Skill::set_development(unsigned short development_) {
    development = std::min(development_, max_development);
}
/*!
 * @brief static member function to set static attributes
 */
void Skill::init_skill() {
    Skill::max_development = 4;
    Skill::base_mana_cost = 15;
    Skill::mana_change = 2;
}

const std::string &Skill::get_name() const {
    return name;
}

/*!
 * @brief increments development
 */
void Skill::upgrade() {
    if(development < Skill::max_development)
        ++development;
}
/*!
 * @brief calculates mana_cost based on base_mana_cost and development
 * @return value of current mana_cost
 */
size_t Skill::get_mana_cost() const {
    return base_mana_cost - (development - 1) * mana_change;
}