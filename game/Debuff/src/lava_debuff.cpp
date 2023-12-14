#include "../include/Debuff.h"

lava_debuff::lava_debuff(const char *name_, size_t dmg_per_tick_) {
    name = std::string(name_);
    dmg_per_tick = dmg_per_tick_;
}

void lava_debuff::apply_on(Creature &target) {
    target.receive_dmg(dmg_per_tick);
}