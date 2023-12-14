#include "../include/Enemy.h"

Enemy::Enemy(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_,
             size_t xp_after_death_): Creature(name_, fraction_, coordinates_) {
    xp_after_death = xp_after_death_;
}

Enemy::Enemy(std::string &name_, Creature::Fraction fraction_, std::pair<size_t, size_t> coordinates_, Stats &stats_,
             size_t xp_after_death_): Creature(name_, fraction_, coordinates_, stats_) {
    xp_after_death = xp_after_death_;
}

/*!
 * @brief setter for xp_after_death attribute
 * @param xp_after_death_ value to be set
 */
void Enemy::set_xp_after_death(size_t xp_after_death_) {
    xp_after_death = xp_after_death_;
}

Enemy::Enemy(Enemy &&other): Creature(static_cast<Creature&&>(other)) {
    xp_after_death = other.xp_after_death;
    other.xp_after_death = 0;
}