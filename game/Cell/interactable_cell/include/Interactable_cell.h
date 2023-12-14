#ifndef LAB3_INTERACTABLE_CELL_H
#define LAB3_INTERACTABLE_CELL_H
#include "../../../Necromant/include/Necromant.h"
class Interactable_cell{
public:
    virtual void on_action_with(Necromant& target) = 0;
};


#endif //LAB3_INTERACTABLE_CELL_H
