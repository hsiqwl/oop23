#include "../include/Essence.h"
Essence::Essence(): Essence(5) {}

Essence::Essence(size_t essence):Cell(Cell::Type::essence), essence(essence) {}

void Essence::on_action_with(Necromant& target) {
    try{
        target.set_essence(target.get_essence() + essence);
        essence = 0;
        set_type(Cell::Type::floor);
    }catch (...) {
        throw;
    }
}

size_t Essence::get_essence() const {
    return essence;
}

void Essence::set_essence(size_t essence_) {
    essence = essence_;
    set_type(Cell::Type::essence);
}