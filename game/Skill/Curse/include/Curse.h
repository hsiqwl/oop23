#ifndef LAB3_CURSE_H
#define LAB3_CURSE_H
#include "../../Skill_interface/include/Skill.h"

class Curse: public Skill{
private:
    static inline size_t base_damage{};
    static inline size_t damage_change{};
public:
    Curse();
    static void init_curse();
    size_t get_damage() const;
    void apply_on(Creature& target) override;
};


#endif //LAB3_CURSE_H
