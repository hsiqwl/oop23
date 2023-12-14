#ifndef LAB3_DESSICATION_H
#define LAB3_DESSICATION_H
#include "../../Skill_interface/include/Skill.h"
#include "../../../Necromant/include/Necromant.h"
#include "../../Matrix/include/matrix.h"
class Dessication_for_mana: public Skill{
private:
    static inline double base_mana_drain_coefficient{};
    static inline double coefficient_change{};
    Necromant* necromant;
public:
    Dessication_for_mana(Necromant* necromant_);
    static void init_dessication();
    double get_coefficient() const;
    void apply_on(Creature& target) override;
};

class Dessication_for_health: public Skill{
private:
    Necromant* necromant;
    static inline double base_health_drain_coefficient{};
    static inline double coefficient_change{};
public:
    Dessication_for_health(Necromant* necromant_);
    static void init_dessication();
    double get_coefficient() const;
    void apply_on(Creature& target) override;
};

#endif //LAB3_DESSICATION_H
