#include "../include/Creature.h"
#include <random>
#include <iostream>
/*!
 * @brief constructor for a Creature type object, uses default constructor for stats
 * @param name_
 * @param fraction_
 * @param coordinates_
 */
Creature::Creature(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_) {
    name = name_;
    fraction = fraction_;
    coordinates = coordinates_;
    Stats();
    is_dead = false;
    is_triggered = false;
}
/*!
 * @brief constructor for a Creature type object, copies stats that are passed as a parameter
 * @param name_
 * @param fraction_
 * @param coordinates_
 * @param stats_
 */
Creature::Creature(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_,
                   Stats &stats_) : Creature(name_, fraction_, coordinates_){
    stats = stats_;
}
/*!
 * @brief a method that calculates damage that is supposed to be dealt to other-parameter and then calling Creature::receive_dmg() inside
 * @param other Creature type object that will be damaged
 */
void Creature::deal_dmg(Creature &other) {
    size_t dmg = stats.get_base_dmg();
    other.receive_dmg(dmg);
}
/*!
 * @brief method that changes curr hp of an object if the damage is not blocked. In case hp is set to zero, calls a Creature::die() method
 * @param dmg
 */
void Creature::receive_dmg(size_t dmg) {
    if(!block_dmg()){
        int new_hp = get_stats().get_curr_hp() - dmg;
        stats.set_curr_hp(std::max(0,new_hp));
        }
    else
    {
        std::cout<<"blocked damage\n";
    }
    if(stats.get_curr_hp() == 0)
        die();
}
/*!
 * @brief this method is invocated if object's curr hp is set to zero. Sets is_dead attribute to true
 */
void Creature::die() {is_dead = true;}

/*!
 * @brief getter for creature's coordinates on map
 * @return a pair representing coordinates on map
 */
const std::pair<size_t, size_t> &Creature::get_coordinates() const {return coordinates;}

/*!
 * @brief changing coordinates attribute
 * @param new_coordinates
 */
void Creature::set_coordinates(std::pair<size_t, size_t> new_coordinates) {
    coordinates = new_coordinates;
}
/*!
 * @brief getter for creature's fraction
 * @return enum type fraction attribute
 */
Creature::Fraction Creature::get_fraction() const {return fraction;}
/*!
 * @brief getter for creature's name
 * @return string containing a name of creature
 */
std::string Creature::get_name() const {return name;}

/*!
 * @brief setting a name for creature
 * @param name_ a string that contains a name
 */
void Creature::set_name(std::string &name_) {
    name = name_;
}
/*!
 * @brief getter for stats attribute
 * @return a reference to Stats type object to creature's stats attribute
 */
const Stats& Creature::get_stats() const {return stats;}
/*!
 * @brief setting new stats, just copies all the information
 * @param stats_ const reference to Stats type object
 */
void Creature::set_stats(const Stats &stats_) {
    stats = stats_;
}
/*!
 * @brief changes coordinates, invocates Creature::set_coordinates()
 * @param x shows a row in a map matrix
 * @param y shows a column in a map matrix
 */
void Creature::move(size_t x, size_t y) {
    set_coordinates(std::make_pair(x,y));
}
/*!
 * @brief sets a fraction
 * @param fraction_ enum type fraction
 */
void Creature::set_fraction(Creature::Fraction fraction_) {fraction = fraction_;}

/*!
 * @brief method decides whether to block incoming damage or not based on given block probability. Uses std::bernoulli_distribution and std::mt19937 random number engine
 * @return bool type showing if the damage will be blocked
 */
bool Creature::block_dmg() {
    std::mt19937 eng(std::random_device{}());
    std::bernoulli_distribution distr(get_stats().get_block_probability());
    return distr(eng);
}
/*!
 * @brief shows if a creatures is still alive
 * @return true if alive, false otherwise
 */
bool Creature::is_alive() const {return !is_dead;}

/*!
 * @brief shows if creature is triggered by something
 * @return true if it's triggered, false otherwise
 */
bool Creature::triggered() const {return is_triggered;}

/*!
 * @brief sets is_triggered attribute to parameter value
 * @param state bool parameter representing if it's triggered or not
 */
void Creature::trigger(bool state) {
    is_triggered = state;
}
/*!
 * @brief move constructor
 * @param other Creature type rvalue reference
 */
Creature::Creature(Creature &&other) {
    name = std::move(other.name);
    fraction = other.fraction;
    stats = other.stats;
    is_dead = other.is_dead;
    is_triggered = other.is_triggered;
    coordinates = other.coordinates;
    //debuff = std::move(other.debuff);
}
/*!
 * @brief return stats of a creature
 * @return Stats type reference
 */
Stats &Creature::get_stats() {
    return stats;
}