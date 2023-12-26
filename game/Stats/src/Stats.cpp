#include "../include/Stats.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

/*!
 *
 * @param base_dmg_ basic settef for damage that creature can have
 */
void Stats::set_base_dmg(size_t base_dmg_) {this->base_dmg = base_dmg_;}

/*!
 *
 * @param probability probability with which a creature can block incoming damage
 */
void Stats::set_block_probability(double probability) {
    if(probability < 0 || probability == 1)
        throw std::invalid_argument("probability can't be less than zero or equal to one");
    this->dmg_block_probability = probability;
}
/*!
 *
 * @param curr_hp_ setting curr_hp. Chooses a minimium between a parameter and max_hp
 */
void Stats::set_curr_hp(size_t curr_hp_) {
        this->curr_hp = std::min(curr_hp_, max_hp);
}
/*!
 *
 * @param curr_level_ setting a curr level of stats, increases/decreases other attributes according to incremential rate
 */
void Stats::set_curr_level(unsigned short curr_level_) {
    curr_level_ = std::min(curr_level_, max_level);
    bool to_increase = curr_level_ > this->curr_level;
    short difference = abs(curr_level_ - this->curr_level);
    while(difference != 0){
        change_stats(to_increase);
        --difference;
        if(to_increase)
            ++this->curr_level;
        else
            --this->curr_level;
    }
}
/*!
 *
 * @param curr_mp_ setting curr_hp. Chooses a minimium between a parameter and max_mp
 */
void Stats::set_curr_mp(size_t curr_mp_) {
    this->curr_mp = curr_mp_ > this->max_mp ? this->max_mp : curr_mp_;
}
/*!
 *
 * @param max_hp_ setter for maximum hp
 */
void Stats::set_max_hp(size_t max_hp_) {
    this->max_hp = max_hp_;
}

/*!
 *
 * @param max_level_ setting the max level, changes current level too, if the new max level is lower that current level
 */
void Stats::set_max_level(unsigned short max_level_) {
    this->max_level = max_level_;
    set_curr_level(std::min(this->max_level, this->curr_level));
}
/*!
 *
 * @param max_mp_ setting max mp
 */
void Stats::set_max_mp(size_t max_mp_) {
    this->max_mp = max_mp_;
    this->curr_mp = std::min(this->curr_mp, this->max_mp);
}
/*!
 * @brief constructor for an object, setting maximum and current values of attributes
 * @param max_hp_ setting max_hp and curr_hp to the value of a parameter
 * @param max_mp_ setting max_mp and curr_mp to the value of a parameter
 * @param base_dmg_ setting base damage
 */
Stats::Stats(size_t max_hp_, size_t max_mp_, size_t base_dmg_) {
    curr_hp = max_hp = max_hp_;
    curr_mp = max_mp = max_mp_;
    base_dmg = base_dmg_;
    curr_level = 1;
    curr_xp = 0;
    max_curr_xp = 0;
    max_level = 1;
    dmg_block_probability = 0;
    incremental_rate = 0;
}

/*!
 * @constructor that is using a default one, setting dmg block probability
 * @param dmg_block_probability
 */
Stats::Stats(double dmg_block_probability): Stats() {
    this->dmg_block_probability = dmg_block_probability;
}
/*!
 * @brief adds xp points and changes level if curr amount of xp is overflowing the maximum amount of curr xp possible
 * @param xp_points added amount of xp_points
 */
void Stats::add_xp(size_t xp_points) {
    size_t levels_up = xp_points / max_curr_xp;
    for(size_t i = 0; i < levels_up; ++i) {
        change_stats(true);
        set_curr_level(curr_level + 1);
    }
    curr_xp += xp_points % max_curr_xp;
    if(curr_xp >= max_curr_xp){
        change_stats(true);
        set_curr_level(curr_level + 1);
        curr_xp = curr_xp % max_curr_xp;
    }
}
/*!
 * @brief decreases/increases attributes according to incremential rate
 * @param to_increase shows if need to increase or decrease attributes
 */
void Stats::change_stats(bool to_increase) {
     double INC = !to_increase ? 1 / get_incremential_rate() : get_incremential_rate();
     curr_hp *= INC;
     max_hp *= INC;
     curr_mp *= INC;
     max_mp *= INC;
     base_dmg *= INC;
}
/*!
 * @brief adds some amount of hp, changing curr_hp
 * @param hp_points added amount of hp
 */
void Stats::add_hp(size_t hp_points) {
    curr_hp = std::min(curr_hp + hp_points, max_hp);
}
/*!
 * @brief adds some amount of hp, changing curr_hp
 * @param mp_points added amount of mp
 */
void Stats::add_mp(size_t mp_points) {
    curr_mp = std::min(curr_mp + mp_points, max_mp);
}

/*!
 * @brief setter for maximun curr hp - attribute that shows how many xp points you need to power up
 * @param max_curr_xp_
 */
void Stats::set_max_curr_xp(size_t max_curr_xp_) {
    max_curr_xp = max_curr_xp_;
}
/*!
 * @brief setting an incremential rate that is used to increase/decrease attributes by some amount
 * @param incremential_rate_
 */
void Stats::set_incremential_rate(double incremential_rate_) {
    incremental_rate = incremential_rate_;
}

Stats::Stats() {
    curr_hp = 0;
    max_hp = 0;
    base_dmg = 0;
    curr_mp = 0;
    max_mp = 0;
    curr_xp = 0;
    curr_level = 0;
    max_level = 0;
    max_curr_xp = 0;
    dmg_block_probability = 0;
    incremental_rate = 0;
}