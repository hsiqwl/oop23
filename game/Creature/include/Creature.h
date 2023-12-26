#ifndef LAB3_CREATURE_H
#define LAB3_CREATURE_H
#include <string>
#include "../../Stats/include/Stats.h"
//#include "../../Debuff/include/Debuff.h"
#include <vector>
#include <memory>
class Creature{
public:
    enum class Fraction{
        undead,
        golem,
        living,
        necromant
    };
private:
    std::string name;
    Fraction fraction;
    Stats stats;
    bool is_dead;
    bool is_triggered;
    std::pair<size_t, size_t> coordinates;
    virtual bool block_dmg();
public:
    Creature(std::string& name_, Fraction fraction_, std::pair<size_t, size_t> coordinates_);
    Creature(std::string & name_, Fraction fraction_, std::pair<size_t, size_t> coordinates_, Stats& stats_);
    Creature(Creature&& other);
    const std::pair<size_t ,size_t>& get_coordinates () const;
    void set_coordinates(std::pair<size_t, size_t> new_coordinates);
    Fraction get_fraction() const;
    void set_fraction(Fraction fraction_);
    const Stats& get_stats() const;
    Stats& get_stats();
    void set_stats(const Stats& stats_);
    std::string get_name() const;
    std::string& get_name(){return name;};
    void set_name(std::string& name_);
    void receive_dmg(size_t dmg);
    void deal_dmg(Creature& other);
    void die();
    void trigger(bool state);
    void move(size_t x, size_t y);
    bool is_alive() const;
    bool triggered() const;
    void set_dead_state(bool state) {is_dead = state;};
};

#endif //LAB3_CREATURE_H
