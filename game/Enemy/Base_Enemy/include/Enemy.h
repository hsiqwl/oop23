#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include "../../../Creature/include/Creature.h"

class Enemy: public Creature{
private:
    size_t xp_after_death;
public:
    Enemy(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_, size_t xp_after_death_);
    Enemy(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_,
          Stats &stats_, size_t xp_after_death_);
    Enemy(Enemy&& other);
    const size_t& get_xp_after_death() const {return xp_after_death;};
    void set_xp_after_death(size_t xp_after_death_);
};

#endif //LAB3_ENEMY_H
