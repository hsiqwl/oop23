#include "../include/Morphism.h"
#include <iostream>
void Morphism::apply_on(Creature &target) {
    try{
        Undead& enemy_target = dynamic_cast<Undead&>(target);
        std::cout<<"applying morphism\n";
        enemy_target.change_attributes(turn_into);
        target.set_stats(enemy_target.get_stats());
        target.set_name(enemy_target.get_name());
        target.set_fraction(Creature::Fraction::undead);
        enemy_target.set_xp_after_death(rand()%100 + 100);
    }catch(std::bad_cast& e){
        throw;
    }
}

Morphism::Morphism(Undead::undead_type type) {
    turn_into = type;
    development = 1;
    switch(type)
    {
        case Undead::undead_type::skeleton:
        {
            name = std::string("Morph into skeleton");
            break;
        }
        case Undead::undead_type::zombie:
        {
            name = std::string("Morph into zombie");
            break;
        }
        case Undead::undead_type::ogre:
        {
            name = std::string("Morph into ogre");
            break;
        }
    }
}

