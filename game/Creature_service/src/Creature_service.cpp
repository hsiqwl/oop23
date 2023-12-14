#include "../include/Creature_service.h"
#include <cmath>
#include <future>
#include <shared_mutex>
/*!
 * @brief constructor for creature service, creates Hero_service and Enemy_service inside
 * @param state_ Game_state type pointer to current game state
 */
Creature_service::Creature_service(Game_state *state_) {
    state = state_;
    hero_service = new Hero_service(state_);
    enemy_service = new Enemy_service(state_);
}
/*!
 * @brief checks if the cell is movable to
 * @param x value of row in a map
 * @param y value of column in a map
 * @return true is it's movable to, false otherwise
 */
bool Creature_service::check_if_movable_to(const size_t &x, const size_t &y) {
    return state->get_curr_map()[x][y]->if_movable_to();
}

/*!
 * @brief moves creature up by changing his coordinates, if it's possible to move up
 * @param target Creature type reference of a creture to be moved
 */
void Creature_service::move_up(Creature& target) {
    std::pair<size_t, size_t> hero_coord = target.get_coordinates();
    if(hero_coord.first > 0 && check_if_movable_to(hero_coord.first - 1, hero_coord.second)){
        hero_coord.first -=1;
        target.set_coordinates(hero_coord);
        state->get_curr_map()[hero_coord.first][hero_coord.second]->set_if_movable_to(false);
        state->get_curr_map()[hero_coord.first + 1][hero_coord.second]->set_if_movable_to(true);
    }
}
/*!
 * @brief moves creature down by changing his coordinates, if it's possible to move down
 * @param target Creature type reference of a creture to be moved
 */
void Creature_service::move_down(Creature& target) {
    std::pair<size_t, size_t> hero_coord = target.get_coordinates();
    if(hero_coord.first < state->get_curr_map().get_rows() - 1 && check_if_movable_to(hero_coord.first + 1, hero_coord.second)){
        hero_coord.first+=1;
        target.set_coordinates(hero_coord);
        state->get_curr_map()[hero_coord.first][hero_coord.second]->set_if_movable_to(false);
        state->get_curr_map()[hero_coord.first - 1][hero_coord.second]->set_if_movable_to(true);
    }
}
/*!
 * @brief moves creature left by changing his coordinates, if it's possible to move left
 * @param target Creature type reference of a creture to be moved
 */
void Creature_service::move_left(Creature& target) {
    std::pair<size_t, size_t> hero_coord = target.get_coordinates();
    if(hero_coord.second > 0 && check_if_movable_to(hero_coord.first,  hero_coord.second - 1)){
        hero_coord.second -= 1;
        target.set_coordinates(hero_coord);
        state->get_curr_map()[hero_coord.first][hero_coord.second]->set_if_movable_to(false);
        state->get_curr_map()[hero_coord.first][hero_coord.second + 1]->set_if_movable_to(true);
    }
}
/*!
 * @brief moves creature right by changing his coordinates, if it's possible to move right
 * @param target Creature type reference of a creture to be moved
 */
void Creature_service::move_right(Creature& target) {
    std::pair<size_t, size_t> hero_coord = target.get_coordinates();
    if(hero_coord.second < state->get_curr_map().get_columns() - 1 && check_if_movable_to(hero_coord.first,  hero_coord.second + 1)){
        hero_coord.second += 1;
        target.set_coordinates(hero_coord);
        state->get_curr_map()[hero_coord.first][hero_coord.second]->set_if_movable_to(false);
        state->get_curr_map()[hero_coord.first][hero_coord.second - 1]->set_if_movable_to(true);
    }
}
/*!
 * @brief moves a creature in a given direction
 * @param target Creature type reference to a creature to be moved
 * @param direction enum type value representing direction towards which target will be moved
 */
void Creature_service::move(Creature& target, Direction direction) {
    std::shared_mutex mux;
    std::unique_lock lock(mux);
    std::pair<size_t ,size_t > old_coord = target.get_coordinates();
    switch (direction) {
        case Direction::up:
            move_up(target);
            break;
        case Direction::down:
            move_down(target);
            break;
        case Direction::right:
            move_right(target);
            break;
        case Direction::left:
            move_left(target);
            break;
        case Direction::none:
            break;
    }
    if(target.get_fraction() != Creature::Fraction::necromant) {
        state->remove_alive_creature(old_coord);
        state->add_alive_creature(target);
    }
    if(check_for_lava(target)){
        burn_from_lava(target);
    }
    if(!target.is_alive())
        handle_creature_death(target);
}
/*!
 * @return returns Game_state type reference to a game state
 */
Game_state& Creature_service::get_state() {return *state;}
/*!
 * @return returns Hero_service type reference to a hero service
 */
Hero_service& Creature_service::get_hero_service() {return *hero_service;}
/*!
 * @return returns Enemy_service type reference to a enemy service
 */
Enemy_service& Creature_service::get_enemy_service() {return *enemy_service;}

/*!
 * @brief check if the second creature is in the attacking range of the first creature
 * @param first Creature type reference to the attacking creature
 * @param second Creature type reference to the to-be-attacked creature
 * @return true if is in the range, false otherwise
 */
bool Creature_service::check_if_within_attack_range(const Creature &first,const Creature &second) {
    double distance = sqrt(pow((int)first.get_coordinates().first - (int)second.get_coordinates().first, 2)
            + pow((int)first.get_coordinates().second - (int)second.get_coordinates().second,2));
    return distance <= sqrt(2);
}
/*!
 * @brief method called to attack second creature by the first one, handles death in case someone dies during the attack
 * @param first Creature type reference to the attacking creature
 * @param second Creature type reference to the to-be-attacked creature
 */
void Creature_service::attack(Creature &first, Creature &second) {
    first.deal_dmg(second);
    if(!second.is_alive()) {
        handle_creature_death(second);
        if(second.get_fraction() != Creature::Fraction::necromant) {
            Enemy *enemy = dynamic_cast<Enemy*>(&second);
            first.get_stats().add_xp(enemy->get_xp_after_death());
        }
    }
}
/*!
 * @brief handles death of a golem by changing landscape and removing it from the game state
 * @param target Golem type reference to an object to be handled
 */
void Creature_service::handle_death(Golem &target) {
    std::pair<size_t ,size_t> coord = target.get_coordinates();
    state->remove_alive_creature(coord);
    switch (target.get_type()) {
        case Golem::golem_type::fire:
        {
            Lava* new_cell = new Lava;
            state->get_curr_map()[coord.first][coord.second] = new_cell;
            break;
        }
        case Golem::golem_type::stone:
        {
            Cell* new_cell = new Cell(Cell::Type::wall);
            delete state->get_curr_map()[coord.first][coord.second];
            state->get_curr_map()[coord.first][coord.second] = new_cell;
            break;
        }
        case Golem::golem_type::essence:
        {
            Essence* new_cell = new Essence;
            state->get_curr_map()[coord.first][coord.second] = new_cell;
            break;
        }
    }
}

/*!
 * @brief handles a death of a Living type creature, deletes it from the alive hash_map and adds to the dead hash_map
 * @param target Living type reference to an object to be handled
 */
void Creature_service::handle_death(Living &target) {
    state->remove_alive_creature(target.get_coordinates());
    std::string name_ = "skeleton";
    Undead* new_target = new Undead(name_, target.get_coordinates(), target.get_xp_after_death(), Undead::undead_type::skeleton);
    state->add_dead_creature(*new_target);
}


/*!
 * @brief handles a death of a Undead type creature, deletes it from the alive hash_map
 * @param target Undead type reference to an object to be handled
 */
void Creature_service::handle_death(Undead &target) {
    state->remove_alive_creature(target.get_coordinates());
}

/*!
 * @brief calculates the next step for a creature via wave-algorithm
 * @param from Creature type reference to the creature from which the path will be calculated
 * @param to Creature type reference to the creature to which the path will be calculated
 * @return enum type Direction representing the direction in which the next step will be taken
 */
Creature_service::Direction Creature_service::get_next_step(Creature &from, Creature &to) {
    std::shared_mutex mux;
    std::shared_lock lk(mux);
    std::pair<size_t ,size_t > from_coord = from.get_coordinates();
    std::pair<size_t ,size_t > to_coord = to.get_coordinates();
    std::vector<int> shortest_path = enemy_service->make_shortest_path(state->get_curr_map(), from_coord, to_coord);
    std::vector<std::pair<size_t,size_t>> steps = enemy_service->get_shortest_path(shortest_path, from_coord, to_coord,
                                                                        state->get_curr_map().get_columns(), state->get_curr_map().get_rows());
    if(steps.empty())
        return Creature_service::Direction::none;
    std::pair<size_t, size_t> next_step = steps[steps.size() - 2];
    if(next_step.first == from_coord.first + 1) {
        return Creature_service::Direction::down;
    }
    else if(next_step.first == from_coord.first - 1) {
        return Creature_service::Direction::up;
    }
    else if(next_step.second == from_coord.second - 1) {
        return Creature_service::Direction::left;
    }
    else {
        return Creature_service::Direction::right;
    }
}

/*!
 * @brief check if the creatures stands on a lava cell
 * @param target Creature type reference to an object which position will be checked
 * @return true is there is lava, false otherwise
 */
bool Creature_service::check_for_lava(Creature &target) {
    std::pair<size_t,size_t> coords = target.get_coordinates();
    Cell::Type type = state->get_curr_map()[coords.first][coords.second]->get_type();
    if(type == Cell::Type::lava)
        return true;
    return false;
}
/*!
 * @brief method that allows a creature take damage from a lava cell if it's standing on one
 * @param target Creature type reference to an object which will take damage
 */
void Creature_service::burn_from_lava(Creature &target) {
    std::pair<size_t,size_t> coords = target.get_coordinates();
    Lava* cell = dynamic_cast<Lava*>(state->get_curr_map()[coords.first][coords.second]);
    target.receive_dmg(cell->get_dmg());
}
/*!
 * @brief handles deaths of creatures of different types including the Necromant type
 * @param target Creature reference type to an object whose death is being handled
 */
void Creature_service::handle_creature_death(Creature &target) {
    switch(target.get_fraction())
    {
        case Creature::Fraction::necromant: {
                Necromant* hero = dynamic_cast<Necromant*>(&target);
                if(hero == nullptr){
                    state->remove_dead_creature(target.get_coordinates());
                }else{
                    hero->set_coordinates({0,0});
                    return;
                }
        }
        case Creature::Fraction::undead:
        {
            Undead& enemy = dynamic_cast<Undead&>(target);
            handle_death(enemy);
            break;
        }
        case Creature::Fraction::living:
        {
            Living& enemy = dynamic_cast<Living&>(target);
            handle_death(enemy);
            break;
        }
        case Creature::Fraction::golem:
        {
            Golem& enemy = dynamic_cast<Golem&>(target);
            handle_death(enemy);
            break;
        }
    }
}

