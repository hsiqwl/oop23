#ifndef LAB3_SKILL_H
#define LAB3_SKILL_H
#include <string>
#include "../../../Creature/include/Creature.h"
/*!
 * @brief an abstract class representing a skill mechanics in a game, which used to inherit from. Has pure virtual method apply_on()
 */
class Skill{
protected:
    std::string name;
    unsigned short development;
    static inline unsigned short max_development{};
    static inline size_t base_mana_cost{};
    static inline size_t mana_change{};
public:
    static void init_skill();
    void set_development(unsigned short development_);
    const std::string& get_name() const;
    void set_name(const std::string& name_);
    virtual size_t get_mana_cost() const;
    virtual void apply_on(Creature& target) = 0;
    virtual void upgrade();
};

#endif //LAB3_SKILL_H
