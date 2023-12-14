#include "../include/Dessication.h"
#include <stdexcept>
#include <iostream>
/*!
 * @brief constructor setting development, name and Necromant type pointer that is stored inside
 * @param necromant_ Necromant type pointer stored inside
 */
Dessication_for_health::Dessication_for_health(Necromant *necromant_) {
    development = 1;
    necromant = necromant_;
    name = static_cast<std::string>("Dessication for health");
}
/*!
 * @brief getter for health_drain_coefficient
 * @return double type value of coefficient attribute
 */
double Dessication_for_health::get_coefficient() const {
    return base_health_drain_coefficient + (development - 1) * coefficient_change;
}

/*!
 * @brief overrided method of Skill abstract class, adds hp to the Necromant stored inside of an object
 * @param target Creature type reference to the target which stats will be used to calculate amount of hp added to necromant
 */
void Dessication_for_health::apply_on(Creature &target) {
    necromant->get_stats().add_hp(target.get_stats().get_max_mp() * get_coefficient());
}

Dessication_for_mana::Dessication_for_mana(Necromant *necromant_) {
    development = 1;
    necromant = necromant_;
    name = static_cast<std::string>("Dessication for mana");
}

double Dessication_for_mana::get_coefficient() const {
    return base_mana_drain_coefficient + (development - 1) * coefficient_change;
}


void Dessication_for_mana::apply_on(Creature &target) {
    necromant->get_stats().add_mp(target.get_stats().get_max_mp() * get_coefficient());
}

void Dessication_for_health::init_dessication() {
    base_health_drain_coefficient = 1.5;
    coefficient_change = 0.05;
}


void Dessication_for_mana::init_dessication() {
    base_mana_drain_coefficient = 1.7;
    coefficient_change = 0.05;
}