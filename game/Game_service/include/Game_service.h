#ifndef GAME_GAME_SERVICE_H
#define GAME_GAME_SERVICE_H
#include "../../Creature_service/include/Creature_service.h"
#include <algorithm>
#include <execution>
#include <thread>
class Game_service{
private:
    Game_state* state;
    Creature_service* creature_service;
    std::pair<size_t ,size_t> find_nearest_opponent(Creature& target);
    void make_move(Creature& enemy);
public:
    Game_state* get_state();
    Creature_service* get_creature_service();
    Game_service(Game_state* state_);
    void act_enemies();
    void act_enemies_mt();
    ~Game_service();
};



#endif //GAME_GAME_SERVICE_H
