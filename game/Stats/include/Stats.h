#ifndef LAB3_STATS_H
#define LAB3_STATS_H
#include <cstddef>
#include "stats_defines.h"
class Stats{
private:
    size_t curr_hp;
    size_t max_hp;
    size_t base_dmg;
    size_t curr_mp;
    size_t max_mp;
    size_t curr_xp;
    unsigned short curr_level;
    unsigned short max_level;
    size_t max_curr_xp;
    double dmg_block_probability;
    double incremental_rate;
    void change_stats(bool to_increase);
public:
    Stats();
    Stats(double dmg_block_probability);
    Stats(size_t max_hp_, size_t max_mp_, size_t base_dmg_);
    Stats(Stats& other) = default;
    void set_max_hp(size_t max_hp_);
    void set_curr_hp(size_t curr_hp_);
    void set_base_dmg(size_t base_dmg_);
    void set_curr_mp(size_t curr_mp_);
    void set_max_mp(size_t max_mp_);
    void set_curr_level(unsigned short curr_level_);
    void set_max_level(unsigned short max_level_);
    void set_block_probability(double probability);
    void set_max_curr_xp(size_t max_curr_xp_);
    void set_incremential_rate(double incremential_rate_);
    double get_incremential_rate() const {return incremental_rate;};
    [[nodiscard]] size_t get_curr_hp() const {return curr_hp;};
    [[nodiscard]] size_t get_max_hp() const {return max_hp;};
    [[nodiscard]] size_t get_curr_mp() const {return curr_mp;};
    [[nodiscard]] size_t get_max_mp() const {return max_mp;};
    [[nodiscard]] size_t get_base_dmg() const {return base_dmg;};
    [[nodiscard]] short get_curr_level() const {return curr_level;};
    [[nodiscard]] short get_max_level() const {return max_level;};
    [[nodiscard]] double get_block_probability() const{return dmg_block_probability;};
    size_t get_curr_xp() const {return curr_xp;};
    size_t get_max_curr_xp() const {return max_curr_xp;};
    void add_xp(size_t xp_points);
    void add_hp(size_t hp_points);
    void add_mp(size_t mp_points);
};


#endif //LAB3_STATS_H
