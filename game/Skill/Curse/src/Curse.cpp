#include "../include/Curse.h"
/*!
 * @brief static member function that sets static attributes
 */
void Curse::init_curse() {
    base_damage = 20;
    damage_change = 2;
}
/*!
 * @brief calculates damage that skill deals based on development
 * @return value of damage to be dealt to something
 */
size_t Curse::get_damage() const {
    return base_damage + (development - 1) * damage_change;
}
/*!
 * @brief overrided function of Skill abstract class, deals damage to target
 * @param target Creature type reference to target to which skill will be applied to
 */
void Curse::apply_on(Creature &target) {
    target.receive_dmg(get_damage());
}
/*!
 * @brief constructor setting a name to "Curse" and development to one
 */
Curse::Curse() {
    name = static_cast<std::string>("Curse");
    development = 1;
}
