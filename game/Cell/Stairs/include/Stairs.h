#ifndef LAB3_STAIRS_H
#define LAB3_STAIRS_H
#include "../../base_cell/include/Cell.h"
#include "../../interactable_cell/include/Interactable_cell.h"

class Stairs: public Cell, public Interactable_cell {
private:
    bool go_up;
public:
    Stairs();

    Stairs(bool direction);

    bool get_direction() const;

    void on_action_with(Necromant& target) override;
};
#endif //LAB3_STAIRS_H
