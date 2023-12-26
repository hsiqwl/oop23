#ifndef GAME_ENEMY_SERVICE_H
#define GAME_ENEMY_SERVICE_H
#include "../../Enemy/Base_Enemy/include/Enemy.h"
#include "../../Game_state/include/Game_state.h"


class Enemy_service{
private:
    Game_state* state;
    bool check_if_within_boundaries(const size_t& x, const size_t& y, const size_t& columns, const size_t& rows);
    matrix<bool> init_for_shortest_path(const matrix<Cell*>& map);
    bool visit(const long long& x, const long long& y, std::vector<bool>& visited, const matrix<bool>& points,
               std::vector<std::pair<size_t , size_t>>& edge_points);
    bool check_if_end(const long long& x, const long long& y, const std::pair<size_t,size_t>& end);
public:
    Enemy_service(Game_state* state_);
    std::vector<int> make_shortest_path(const matrix<Cell*>& map,const std::pair<size_t, size_t>& start,
                                           const std::pair<size_t, size_t>& end);
    std::vector<int> make_shortest_path_mt(const matrix<Cell*>& map,const std::pair<size_t, size_t>& start,
                                        const std::pair<size_t, size_t>& end);
    std::vector<std::pair<size_t, size_t>> get_shortest_path(const std::vector<int>& wave_lengths,const std::pair<size_t, size_t>& start,
                                                             const std::pair<size_t, size_t>& end, const size_t& columns, const size_t& rows);
    bool check_if_within_triggering_radius(const std::pair<size_t,size_t>& first,const std::pair<size_t,size_t>& second);
};

#endif //GAME_ENEMY_SERVICE_H
