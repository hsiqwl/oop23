#include "../include/Game_state.h"
#include <stdexcept>
/*!
 * @brief constructor
 * @param necromant_ Necromat type pointet to the main hero
 * @param alive hash_map containing creatures and their coordinates
 * @param map vector of matrixes of Cell type pointers that represents different level maps
 */
Game_state::Game_state(Necromant* necromant_, std::unordered_map<std::pair<size_t, size_t>, Creature*, pair_hash>& alive,
                       std::vector<matrix<Cell *>>& map) {
    alive_creatures = alive;
    necromant = necromant_;
    dungeon_map = map;
    curr_level = 1;
}
/*!
 * @brief searches for an alive creatures with given coordinates
 * @param coordinates pair of coordinates to be found in a alive creatures hash_nap
 * @return Creature type pointer to a creature with given coordinates
 * @throws std::logic_error if coordinates are not found
 */
Creature *Game_state::get_alive_creature_by_coordinates(std::pair<size_t, size_t> coordinates) {
    auto it = alive_creatures.find(coordinates);
    if(it!=alive_creatures.end()) {
        return it->second;
    }
    else
        throw std::logic_error("didnt find creature in alive map");
}
/*!
 * @brief searches for a dead creatures with given coordinates
 * @param coordinates pair of coordinates to be found in dead creatures map
 * @return Creature type pointer to currently dead creature
 * @throws std::logic_error if coordinates are not found
 */
Creature* Game_state::get_dead_creature_by_coordinates(std::pair<size_t, size_t> coordinates){
    auto it = dead_useful_creatures.find(coordinates);
    if(it!=dead_useful_creatures.end()) {
        return it->second;
    }
    else
        throw std::logic_error("didnt find creature in the dead map");
}

/*!
 * @brief adds creatures and his coordinates to alive creature hash map, also changes properties of a map
 * @param target Creature type reference to an object to be added
 * @throws std::logic_error if there's already an object with the same coordinates
 */
void Game_state::add_alive_creature(Creature &target) {
    std::pair<size_t , size_t> coord = target.get_coordinates();
    auto it = alive_creatures.insert(std::make_pair(target.get_coordinates(), &target));
    if(!it.second)
        throw std::logic_error("there is a creature with same coordinates");
    else
        dungeon_map[curr_level - 1][coord.first][coord.second]->set_if_movable_to(false);
}
/*!
 * @brief  adds creatures and his coordinates to dead creature hash map
 * @param target Creature type reference to an object to be added
 */
void Game_state::add_dead_creature(Creature &target) {
    dead_useful_creatures.erase(target.get_coordinates());
    dead_useful_creatures.insert(std::make_pair(target.get_coordinates(), &target));
}
/*!
 * @brief deletes a creature with given coordinates from alive creature hash map, also changes properties of a map
 * @param coordinates pair of coordinates of a creature to be deleted
 */
void Game_state::remove_alive_creature(const std::pair<size_t,size_t>& coordinates) {
        alive_creatures.erase(coordinates);
        dungeon_map[curr_level - 1][coordinates.first][coordinates.second]->set_if_movable_to(true);
}
/*!
 * @brief deletes a creature with given coordinates from dead creature hash map
 * @param coordinates pair of coordinates of a creature to be deleted
 */
void Game_state::remove_dead_creature(const std::pair<size_t,size_t>& coordinates) {
    dead_useful_creatures.erase(coordinates);
}

/*!
 * @brief destructor frees all the resourses stored in an  object
 */
Game_state::~Game_state()
{
    delete necromant;
    necromant = nullptr;
    auto it = alive_creatures.begin();
    while(it != alive_creatures.end()) {
        delete it->second;
        ++it;
    }
    it = dead_useful_creatures.begin();
    while(it != dead_useful_creatures.end()){
        delete it->second;
    }
    for(int i = 0; i < dungeon_map.size(); ++i) {
        for (int j = 0; j < dungeon_map[i].get_rows(); ++j) {
            for (int k = 0; k < dungeon_map[i][j].size(); ++k) {
                delete dungeon_map[i][j][k];
            }
        }
    }
}



