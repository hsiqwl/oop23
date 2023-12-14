#ifndef LAB3_NECROMASTERY_H
#define LAB3_NECROMASTERY_H
#include "../../Skill_interface/include/Skill.h"
#include "../../../Enemy/Undead/include/Undead.h"
#include <libconfig.h++>
class Necromastery: public Skill{
private:
    Undead::undead_type resurrect_type;
public:
    Necromastery(Undead::undead_type ressurect_type_);
    void apply_on(Creature& target) override;
};


#endif //LAB3_NECROMASTERY_H
