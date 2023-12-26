#ifndef GAME_GAME_SERVICE_H
#define GAME_GAME_SERVICE_H
#include "../../Creature_service/include/Creature_service.h"
#include <algorithm>
#include <execution>
#include <thread>
#include <syncstream>
class Game_service{
private:
    Game_state* state;
    Creature_service* creature_service;
    std::pair<size_t ,size_t> find_nearest_opponent(Creature& target);
    void make_move(Creature& enemy);

    template<typename ItIn, typename ItOut>
    void func(ItIn first, ItIn last, ItOut first_out, const std::pair<size_t, size_t>& to, std::shared_mutex& mutex)
    {
        for(; first!=last; first++)
        {
            std::shared_lock lock(mutex);
            Creature_service::Direction dir = creature_service->get_next_step_mt(*first, to, state->get_curr_map());
            lock.unlock();
            std::unique_lock u_lock(mutex);
            *first_out = dir;
            ++first_out;
            u_lock.unlock();
        }
    }

    template<typename ItIn, typename ItOut>
    void calculate_step(ItIn first, ItIn last, ItOut first_out, const std::pair<size_t, size_t>& to, std::shared_mutex& mutex)
    {
        auto thread_num = std::thread::hardware_concurrency();
        std::vector<std::jthread> threads(thread_num);
        auto elements = std::distance(first, last);
        for(size_t i = 0; i < thread_num; ++i){
            size_t start_i = i * elements / thread_num;
            size_t end_i = (i + 1) * elements / thread_num;
            auto start = std::next(first, start_i);
            auto end = std::next(first, end_i);
            auto res_start = std::next(first_out, start_i);
            threads[i] = std::jthread([this, &start, &end, &res_start, &to, &mutex](){func(start, end, res_start, to, mutex);});
        }
    }

public:
    Game_state* get_state();
    Creature_service* get_creature_service();
    Game_service(Game_state* state_);
    void act_enemies();
    void act_enemies_mt();
    ~Game_service();
};



#endif //GAME_GAME_SERVICE_H
