#include "../include/Necromastery.h"

void Necromastery::apply_on(Creature &target) {
    Undead &enemy = dynamic_cast<Undead &>(target);
    enemy.change_attributes(resurrect_type);
    target.set_name(enemy.get_name());
    target.set_fraction(Creature::Fraction::necromant);
    target.set_stats(enemy.get_stats());
    enemy.set_xp_after_death(rand()%100 + 100);
}

Necromastery::Necromastery(Undead::undead_type ressurect_type_) {
    name = "Necromastery";
    development = 1;
    resurrect_type = ressurect_type_;
}