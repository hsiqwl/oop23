#include "../include/Hero_service.h"
#include <stdexcept>
#include <cmath>
/*!
 * @brief constructor for an object
 * @param state_ Game_state type pointer to the state of the game
 */
Hero_service::Hero_service(Game_state *state_): state(state_) {}

/*!
 * @brief method used to cast a skill with given name to the creature with the given coordinates
 * @param skill_name string that contains the name of the  skill
 * @param coordinates pair of coordinates which a creature possesses
 */
void Hero_service::cast_skill(const std::string &skill_name, const std::pair<size_t, size_t> &coordinates) {
    if(!check_if_can_apply_skill(coordinates))
        return;
    Skill* skill = state->get_necromant().choose_skill(skill_name);
    if(state->get_necromant().get_stats().get_curr_mp() < skill->get_mana_cost()) {
        return;
    }
    try {
        if (skill_name.find("Dessication") != std::string::npos ||
            skill_name.find("Necromastery") != std::string::npos) {
            Creature *target = state->get_dead_creature_by_coordinates(coordinates);
            skill->apply_on(*target);
        } else {
            Creature *target = state->get_alive_creature_by_coordinates(coordinates);
            skill->apply_on(*target);
        }
        state->get_necromant().get_stats().set_curr_mp(
                std::max(0, (int) state->get_necromant().get_stats().get_curr_mp() - (int) skill->get_mana_cost()));
    }catch (...) {
        std::cout<<"catching an exception\n";
        return;
    }
}
/*!
 * @brief method used to interact with an interactable cell on the map, invocates Interactable_cell::on_action_with() method
 * @param coordinates pair of coordinates of a cell to interact with
 */
void Hero_service::interact_with_cell(const std::pair<size_t, size_t> &coordinates) {
    try {
        Interactable_cell &cell = dynamic_cast<Interactable_cell &>(*state->get_curr_map()[coordinates.first][coordinates.second]);
        cell.on_action_with(state->get_necromant());
        if(state->get_curr_map()[coordinates.first][coordinates.second]->get_type() == Cell::Type::stairs)
        {
            if(static_cast<Stairs*>(state->get_curr_map()[coordinates.first][coordinates.second])->get_direction()) {
                state->set_level(state->get_level() + 1);
            }
            else {
                state->set_level(std::max(state->get_level() - 1, 0));
            }
        }
    }
    catch (std::bad_cast &e) {
        return;
    }
}
/*!
 * @brief checking if the hero is in range of casting a skill to a certain point on the map
 * @param coordinates pair of coordinates to which a skill will be applied
 * @return bool value. True if is in range, false otherwise
 */
bool Hero_service::check_if_can_apply_skill(const std::pair<size_t, size_t> &coordinates) {
    std::pair<size_t ,size_t> hero_coord = state->get_necromant().get_coordinates();
    float dist = sqrt(pow((int)hero_coord.first - (int)coordinates.first,2) + pow((int)hero_coord.second - (int)coordinates.second,2));
    if(dist <= 2)
        return true;
    return false;
}