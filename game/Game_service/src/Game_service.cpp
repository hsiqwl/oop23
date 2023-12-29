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
    throw std::out_of_range("no such creatures");
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

void Game_service::make_move_mt(Creature& enemy, std::shared_mutex& mutex) {
    Necromant& hero = state->get_necromant();
    if(enemy.get_fraction() != Creature::Fraction::necromant) {
        bool is_in_triggering_raduis = creature_service->get_enemy_service().check_if_within_triggering_radius(
                enemy.get_coordinates(), hero.get_coordinates());
        if (is_in_triggering_raduis) {
            enemy.trigger(true);
        }
        if (enemy.triggered()) {
            if (creature_service->check_if_within_attack_range(enemy.get_coordinates(), hero.get_coordinates())) {
                creature_service->attack_mt(enemy, hero, mutex);
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
    auto trig = [this](std::pair<const std::pair<size_t,size_t>, Creature*>& enemy){
        if(creature_service->get_enemy_service().check_if_within_triggering_radius(enemy.first, state->get_necromant().get_coordinates())){
            enemy.second->trigger(true);
        }
    };
    std::for_each(std::execution::par, state->get_alive_creatures().begin(), state->get_alive_creatures().end(), trig);

    std::mutex mutex;
    auto spread = [this,&mutex, &enemies, &creatures](std::pair<const std::pair<size_t,size_t>, Creature*>& enemy){
        if(enemy.second->triggered()){
            if(creature_service->check_if_within_attack_range(enemy.first, state->get_necromant().get_coordinates())){
                std::unique_lock locker(mutex);
                enemies.emplace_back(enemy.second);
            }else{
                std::unique_lock locker(mutex);
                creatures.emplace_back(enemy.second->get_coordinates());
            }
        }
    };
    std::for_each(std::execution::par, state->get_alive_creatures().begin(), state->get_alive_creatures().end(), spread);

    std::vector<Creature*> dead_after_attacks;
    auto attacking = [this,&dead_after_attacks,&mutex](Creature* target){
        if(target->is_alive()){
            try {
                auto coor = find_nearest_opponent(*target);
                Creature &second = *state->get_alive_creature_by_coordinates(coor);
                target->deal_dmg(second);
                if (!second.is_alive()) {
                    std::unique_lock locker(mutex);
                    dead_after_attacks.emplace_back(&second);
                }
            }catch(...){
                return;
            }
        }
    };
    std::for_each(std::execution::par, enemies.begin(), enemies.end(), attacking);
    for(int i = 0; i < dead_after_attacks.size(); ++i){
        get_creature_service()->handle_creature_death(*dead_after_attacks[i]);
    }
    std::vector<Creature_service::Direction> directions(creatures.size());
    std::shared_mutex mutex_1;
    calculate_step(creatures.begin(), creatures.end(), directions.begin(), state->get_necromant().get_coordinates(), mutex_1);
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