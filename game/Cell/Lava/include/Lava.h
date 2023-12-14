#ifndef LAB3_LAVA_H
#define LAB3_LAVA_H
#include "../../base_cell/include/Cell.h"
#include <stddef.h>
#define DEFAULT_DAMAGE 3
class Lava: public Cell{
private:
    size_t dmg_per_tick;
public:
    size_t get_dmg() const;
    Lava();
    Lava(size_t dmg_per_tick);
};


#endif //LAB3_LAVA_H
