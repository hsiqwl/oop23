#include "../include/Game_service.h"
#include <shared_mutex>
#include <mutex>
Game_service::Game_service(Game_state *state_) {
    state = state_;
    creature_service = new Creature_service(state_);
}

Creature_service *Game_service::get_creature_service() {
    return creature_service;
}

Game_state *Game_service::get_state() {return state;}

std::pair<size_t, size_t> Game_service::find_nearest_opponent(Creature& target) {
    auto it = state->get_alive_creatures().begin();
    while(it != state->get_alive_creatures().end())
    {
        if(get_creature_service()->check_if_within_attack_range(target.get_coordinates(), it->second->get_coordinates())
            && target.get_fraction() != it->second->get_fraction()) {
            return it->first;
        }
        ++it;
    }
    return {0,0};
}


void Game_service::make_move(Creature& enemy) {
    Necromant& hero = state->get_necromant();
    if(enemy.get_fraction() != Creature::Fraction::necromant) {
        bool is_in_triggering_raduis = creature_service->get_enemy_service().check_if_within_triggering_radius(
                enemy.get_coordinates(), hero.get_coordinates());
        if (is_in_triggering_raduis) {
            enemy.trigger(true);
        }
        if (enemy.triggered()) {
            if (creature_service->check_if_within_attack_range(enemy.get_coordinates(), hero.get_coordinates())) {
                creature_service->attack(enemy, hero);
                if(!hero.is_alive()) {
                    std::cout<<"hero dead, returning from make_move()\n";
                    return;
                }
            }
            else {
                Creature_service::Direction direction = creature_service->get_next_step(enemy.get_coordinates(), hero.get_coordinates());
                creature_service->move(enemy, direction);
            }
        }
    }else{
        auto coord = find_nearest_opponent(enemy);
        try {
            creature_service->attack(enemy, *state->get_alive_creature_by_coordinates(coord));
        }catch (...){
            return;
        }
    }
}

void Game_service::act_enemies() {
    std::vector<Creature*> enemies;
    std::vector<std::pair<size_t, size_t>> creatures;
    auto it = state->get_alive_creatures().begin();
    auto end = state->get_alive_creatures().end();
    while(it!=end){
        if(creature_service->get_enemy_service().check_if_within_triggering_radius(it->first, state->get_necromant().get_coordinates())){
            it->second->trigger(true);
        }
        if(it->second->triggered()){
            if(creature_service->check_if_within_attack_range(it->first, state->get_necromant().get_coordinates())){
                enemies.emplace_back(it->second);
            }else{
                creatures.emplace_back(it->second->get_coordinates());
            }
        }
        ++it;
    }
    for(int i = 0; i < enemies.size(); ++i) {
        creature_service->attack(*enemies[i],state->get_necromant());
        if(!state->get_necromant().is_alive()){
            std::cout<<"hero dead, returning from act_enemies\n";
            return;
        }
    }
    for(int i = 0; i < creatures.size(); ++i){
        Creature_service::Direction dir = creature_service->get_next_step(creatures[i], state->get_necromant().get_coordinates());
        creature_service->move(*state->get_alive_creature_by_coordinates(creatures[i]), dir);
    }
}

void Game_service::act_enemies_mt() {
    std::vector<Creature*> enemies;
    std::vector<std::pair<size_t,size_t>> creatures;
    auto it = state->get_alive_creatures().begin();
    auto end = state->get_alive_creatures().end();
    while(it!=end){
        if(creature_service->get_enemy_service().check_if_within_triggering_radius(it->first, state->get_necromant().get_coordinates())){
            it->second->trigger(true);
        }
        if(it->second->triggered()) {
            if (creature_service->check_if_within_attack_range(it->first, state->get_necromant().get_coordinates())) {
                enemies.emplace_back(it->second);
            } else {
                creatures.emplace_back(it->second->get_coordinates());
            }
        }
        ++it;
    }
    for(int i = 0; i < enemies.size(); ++i){
        creature_service->attack(*enemies[i],state->get_necromant());
        if(!state->get_necromant().is_alive()) {
            std::cout<<"hero dead, returning from make_move()\n";
            return;
        }
    }
    std::vector<Creature_service::Direction> directions(creatures.size());
    std::shared_mutex mutex;
    calculate_step(creatures.begin(), creatures.end(), directions.begin(), state->get_necromant().get_coordinates(), mutex);
    for(int i = 0; i < creatures.size(); ++i){
        creature_service->move(*state->get_alive_creature_by_coordinates(creatures[i]), directions[i]);
    }
}


Game_service::~Game_service() {
    delete state;
    delete &creature_service->get_enemy_service();
    delete &creature_service->get_hero_service();
    delete creature_service;
}