#include "../include/Cell.h"

Cell::Cell() {
    type = Type::floor;
    is_movable_to = true;
}

Cell::Cell(Cell::Type type_) {
    type = type_;
    if(type == Type::floor || type == Type::essence || type == Type::lava || type == Type::stairs)
        is_movable_to = true;
    else
        is_movable_to = false;
}