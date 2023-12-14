#ifndef LAB3_ESSENCE_H
#define LAB3_ESSENCE_H
#include "../../base_cell/include/Cell.h"
#include "../../interactable_cell/include/Interactable_cell.h"
#define DEFAULT_ESSENCE 10
class Essence: public Cell, public Interactable_cell{
private:
    size_t essence;
public:
    size_t get_essence() const;
    void set_essence(size_t essence_);
    void on_action_with(Necromant& target) override;
    Essence();
    Essence(size_t essence);
};

#endif //LAB3_ESSENCE_H
