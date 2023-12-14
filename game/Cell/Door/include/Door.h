#ifndef LAB3_DOOR_H
#define LAB3_DOOR_H
#include "../../base_cell/include/Cell.h"
#include "../../interactable_cell/include/Interactable_cell.h"

class Door: public Cell, public Interactable_cell{
private:
    bool is_open;
public:
    Door();
    bool get_state() const;
    void open();
    void close();
    void on_action_with(Necromant& target) override;
};

#endif //LAB3_DOOR_H
