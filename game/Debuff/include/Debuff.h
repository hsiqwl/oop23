#ifndef LAB3_DEBUFF_H
#define LAB3_DEBUFF_H
#include <string>
#include "../../Creature/include/Creature.h"
#include "defines.h"
class Debuff{
protected:
    std::string name;
public:
    [[nodiscard]] const std::string& get_name() const {return name;};
    virtual void apply_on(Creature& target) = 0;
};

class lava_debuff: public Debuff {
private:
    size_t dmg_per_tick;
public:
    lava_debuff(const char* name_ = "burning floor", size_t dmg_per_tick_ = DEFAULT_LAVA_DMG);
    void apply_on(Creature& target) override;
};

#endif //LAB3_DEBUFF_H
