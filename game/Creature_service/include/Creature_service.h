#ifndef GAME_CREATURE_SERVICE_H
#define GAME_CREATURE_SERVICE_H
#include "../../Enemy_service/include/Enemy_service.h"
#include "../../Hero_service/include/Hero_service.h"
#include "../../Enemy/Golem/include/Golem.h"
#include "../../Enemy/Living/include/Living.h"
#include "../../Enemy/Undead/include/Undead.h"
#include "../../Cell/Lava/include/Lava.h"
#include "../../Cell/Essence/include/Essence.h"


class Creature_service{
public:
    enum class Direction{
        up,
        down,
        right,
        left,
        none
    };
private:
    Game_state* state;
    Hero_service* hero_service;
    Enemy_service* enemy_service;
    void move_up(Creature& target);
    void move_down(Creature& target);
    void move_right(Creature& target);
    void move_left(Creature& target);
    bool check_for_lava(Creature& target);
    void burn_from_lava(Creature& target);
    bool check_if_movable_to(const size_t& x, const size_t& y);
    void handle_death(Golem& target);
    void handle_death(Undead& target);
    void handle_death(Living& target);
public:
    void handle_creature_death(Creature& target);
    bool check_if_within_attack_range(const std::pair<size_t, size_t> &first,
                                      const std::pair<size_t, size_t> &second);
    Creature_service(Game_state* state_);
    Direction get_next_step(const std::pair<size_t, size_t>& from, const std::pair<size_t, size_t>& to) const;
    Direction get_next_step_mt(const std::pair<size_t, size_t>& from, const std::pair<size_t, size_t>& to, const matrix<Cell*>& map) const;
    void move(Creature& target, Direction direction);
    void attack(Creature& first, Creature& second);
    Game_state& get_state();
    Hero_service& get_hero_service();
    Enemy_service& get_enemy_service();
};


#endif //GAME_CREATURE_SERVICE_H
