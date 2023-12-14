#include "../include/Necromant.h"
#include <stdexcept>
Necromant::Necromant(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_):
    Creature(name_, fraction_, coordinates_) {
    essence = 0;
    max_minions = 3;
    curr_minions = 0;
    skill_points = 0;
}

Necromant::Necromant(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_, Stats& stats_):
    Creature(name_, fraction_, coordinates_, stats_) {
    essence = 0;
    max_minions = 3;
    curr_minions = 0;
    skill_points = 5;
}

/*!
 * @brief method that add's a new Skill type pointer into skill_map if there're available skill points
 * @param skill Skill type reference to a new skill
 * @throws std::logic_error if no skill point available
 */
void Necromant::learn_skill(Skill& skill) {
    if(skill_points == 0)
        throw std::logic_error("no skill points available");
    skill_map.insert(std::make_pair(skill.get_name(), &skill));
    skill_points--;
}

/*!
 * @brief searches for a Skill type object with given name
 * @param skill_name name of a skill to be found
 * @return Skill type pointer
 * @throws std::logic_error if no such skill with given name is in skill_map
 */
Skill* Necromant::choose_skill(const std::string &skill_name) {
    auto it = skill_map.find(skill_name);
    if(it!=skill_map.end())
        return it->second;
    else
        throw std::logic_error("no such skill");
}

/*!
 * @brief upgrades certain Skill by invocating Skill::upgrade() if skill point is available
 * @param skill Skill type reference to an object to be upgraded
 * @throws std::logic_error if there're no points available
 */
void Necromant::upgrade_skill(Skill &skill) {
    if(skill_points == 0)
        throw std::logic_error("no skill points available");
    skill.upgrade();
    skill_points--;
}
/*!
 * @brief getter for essence attribute
 * @return size_t value of curr essence stored
 */
size_t Necromant::get_essence() const noexcept {
    return essence;
}
/*!
 * @brief setter for essence attribute
 * @param essence_ size_t value of essence to be set
 */
void Necromant::set_essence(size_t essence_) noexcept {
    essence = essence_;
}
/*!
 * @brief shows a number of maximum minions that a hero can make
 * @return size_t value of max_minions attribute
 */
size_t Necromant::get_max_minions() const noexcept {
    return max_minions;
}
/*!
 * @brief setter for max_minions
 * @param max_minions_ size_t value to be set
 */
void Necromant::set_max_minions(size_t max_minions_) noexcept {
    max_minions = max_minions_;
}
/*!
 * @brief shows available number of skill points
 * @return unsigned short value of skill_points attribute
 */
unsigned short Necromant::get_skill_points() const noexcept {
    return skill_points;
}
/*!
 * @brief setter for skill_points attribute
 * @param skill_points_ unsigned short value to be set
 */
void Necromant::set_skill_points(unsigned short skill_points_) noexcept {
    skill_points = skill_points_;
}
/*!
 * @brief destructor that frees resourses used by an object
 */
Necromant::~Necromant() {
    auto it = skill_map.begin();
    while(it!=skill_map.end()) {
        delete it->second;
        ++it;
    }
}