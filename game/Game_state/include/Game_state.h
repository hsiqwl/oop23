#ifndef LAB3_GAME_H
#define LAB3_GAME_H
#include "../../Matrix/include/matrix.h"
#include "../../Necromant/include/Necromant.h"
#include "../../Cell/base_cell/include/Cell.h"
#include "../../Stairs/include/Stairs.h"
#include <vector>
struct pair_hash{
    size_t operator()(const std::pair<size_t,size_t>& pair_) const noexcept{
        size_t h1 = std::hash<size_t>{}(pair_.first);
        size_t h2 = std::hash<size_t>{}(pair_.second);
        return h1 ^ h2;
    }
};

/*!
 * @brief a class that contains info about game's current state such as the map, the hero, alive and dead useful creatures. This class is used as a repository class
 */
class Game_state{
private:
    Necromant* necromant;
    std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash> alive_creatures;
    std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash> dead_useful_creatures;
    short curr_level;
    std::vector<matrix<Cell*>> dungeon_map;
public:
    Game_state() = delete;
    Game_state(Necromant* necromant_, std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash>& alive, std::vector<matrix<Cell*>>& map);
    Necromant& get_necromant() noexcept{return *necromant;};
    short get_level() const noexcept{return curr_level;};
    void set_level(short level) {curr_level = level;};
    matrix<Cell*>& get_curr_map() {return dungeon_map[curr_level - 1];};
    const matrix<Cell*>& get_curr_map() const {return dungeon_map[curr_level - 1];};
    std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash>& get_alive_creatures() {return alive_creatures;};
    std::unordered_map<std::pair<size_t,size_t>, Creature*, pair_hash>& get_dead_creatures() {return dead_useful_creatures;};
    Creature* get_alive_creature_by_coordinates(std::pair<size_t,size_t> coordinates);
    Creature* get_dead_creature_by_coordinates(std::pair<size_t,size_t> coordinates);
    void add_dead_creature(Creature& target);
    void add_alive_creature(Creature& target);
    void remove_dead_creature(const std::pair<size_t,size_t>& coordinates);
    void remove_alive_creature(const std::pair<size_t,size_t>& coordinates);
    unsigned short get_max_level() const {return dungeon_map.size();};
    ~Game_state();
};


#endif //LAB3_GAME_H
