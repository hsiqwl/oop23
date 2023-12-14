#include "../include/Lava.h"

Lava::Lava(size_t dmg_per_tick): Cell(Cell::Type::lava), dmg_per_tick(dmg_per_tick){}

Lava::Lava(): Lava(5){}

size_t Lava::get_dmg() const {
    return dmg_per_tick;
}