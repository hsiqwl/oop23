#include "../include/Stairs.h"

Stairs::Stairs(bool direction):Cell(Cell::Type::stairs), go_up(direction) {}

Stairs::Stairs(): Stairs(false){}

bool Stairs::get_direction() const {
    return go_up;
}

void Stairs::on_action_with(Necromant& target) {
    return;
}