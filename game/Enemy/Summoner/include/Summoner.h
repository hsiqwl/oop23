#ifndef LAB3_SUMMONER_H
#define LAB3_SUMMONER_H
#include "../../Undead/include/Undead.h"
#include "../../Living/include/Living.h"
#include "../../../Cell/base_cell/include/Cell.h"
class Summoner{
public:
    virtual void summon_enemy(Cell& cell) = 0;
};

class Summoner_undead: public Undead, public Summoner{
public:
    void summon_enemy(Cell& cell) override;
};

class Summoner_living: public Living, public Summoner{
public:
    void summon_enemy(Cell& cell) override;
};
#endif //LAB3_SUMMONER_H
