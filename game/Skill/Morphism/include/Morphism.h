#ifndef LAB3_MORPHISM_H
#define LAB3_MORPHISM_H
#include "../../Skill_interface/include/Skill.h"
#include "../../../Enemy/Undead/include/Undead.h"
class Morphism: public Skill{
private:
    Undead::undead_type turn_into;
public:
    Undead::undead_type get_turning_type() const {return turn_into;};
    Morphism(Undead::undead_type type);
    void apply_on(Creature& target) override;
};

#endif //LAB3_MORPHISM_H
