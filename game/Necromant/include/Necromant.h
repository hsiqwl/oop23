#ifndef LAB3_NECROMANT_H
#define LAB3_NECROMANT_H
#include "../../Creature/include/Creature.h"
#include "../../Skill/Skill_interface/include/Skill.h"
#include <unordered_map>
class Necromant: public Creature{
private:
    size_t essence;
    size_t max_minions;
    size_t curr_minions;
    unsigned short skill_points;
    std::unordered_map<std::string, Skill*> skill_map;
public:
    Necromant(std::string& name_, Fraction fraction_, std::pair<size_t, size_t> coordinates_);
    Necromant(std::string & name_, Fraction fraction_, std::pair<size_t, size_t> coordinates_, Stats& stats_);
    void learn_skill(Skill& skill);
    size_t get_essence() const noexcept;
    void set_essence(size_t essence_) noexcept;
    size_t get_max_minions() const noexcept;
    size_t get_curr_minions() const {return  curr_minions;};
    void set_curr_minions(size_t minions) { curr_minions = minions;};
    void set_max_minions(size_t max_minions_) noexcept;
    unsigned short get_skill_points() const noexcept;
    void set_skill_points(unsigned short skill_points_) noexcept;
    void upgrade_skill(Skill& skill);
    Skill* choose_skill(const std::string& skill_name);
    ~Necromant();
};

#endif //LAB3_NECROMANT_H
