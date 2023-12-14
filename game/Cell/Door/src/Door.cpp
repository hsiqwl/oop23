#include "../include/Door.h"

Door::Door(): Cell(Cell::Type::door){
    is_open = false;
    set_if_movable_to(false);
}

bool Door::get_state() const {
    return is_open;
}

void Door::close() {
    is_open = false;
    set_if_movable_to(false);
}

void Door::open() {
    is_open = true;
    set_if_movable_to(true);
}

void Door::on_action_with(Necromant& target) {
    set_if_movable_to(!get_state());
    is_open = !is_open;
}